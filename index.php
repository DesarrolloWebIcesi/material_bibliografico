<script type="text/javascript">
//Refresca la página cada 20 minutos y un segundo
function timedRefresh(timeoutPeriod) {
	setTimeout("location.reload(true);",timeoutPeriod);
}
//timedRefresh(1200001);
</script>

<?php
session_start();

//Reirecciona a HTTPS si se usa HTTP
/*if ($_SERVER['SERVER_NAME'] != "http://".$_SERVER['SERVER_NAME']){
	$port = $_SERVER["SERVER_PORT"];
	$ssl_port = "443"; //443 es el puerto por defecto de HTTPS
	if ($port != $ssl_port){
		$host = $_SERVER["HTTP_HOST"];
		$uri = getenv('REQUEST_URI');
		header("Location: https://$host$uri");
		die;
	}
}*/

//Si el index es llamado desde fuera del contexto de Joomla entonces se redireciona a este.
if (strpos(getenv('REQUEST_URI'), 'material_bibliografico') !== FALSE){
  header("Location: ../obtencion_de_documentos.php");
  die;
}

?>
<script src="material_bibliografico/js/cadenas.js" type="text/javascript"></script>
<script src="material_bibliografico/js/validacionesAdquisiciones.js" type="text/javascript"></script>
<link rel="stylesheet" media="all" type="text/css" href="material_bibliografico/css_formularios.css" />

<div id="contenido_index">
    <table align="center">
      <tr>
	    <td>
	      <?php
	        //Si hay datos en la sesión el usuario ya se logueó, entonces se muestran sus datos y la opción salir encima del contenido
            include "datos_encabezado.php";
	      ?>
	    </td>
      </tr>
      <tr>
	    <td>
	      <?php
            if (!$_SESSION['idUsuario']){
			  //El usuario no se ha logueado
              if (!$_POST['boton']) {
                //Es la primiera vez que se entra a login.php
				include "login.php";
              }else{
			    //Se valida contra el LDAP el usuario y la contraseña ingresados
                include "autentica.inc";
                $autentica = new autentica();
                $resultadoAutenticacion = $autentica->autenticarUsuario($_POST['usuario'], $_POST['password']);
                
				switch($resultadoAutenticacion){
				  case 0:
				    //Se hace un re-direct a la página con la que se entró al sitio, ya que se entra directamente con el tipo de solicitud ya elegido
				    header("Location: ".getenv("HTTP_REFERER"));
				    break;
				  case 1:
				    include "login.php";
					echo "<br/><div class='error'>
					     Al parecer usted no est&aacute; registrado en el <a href='https://".$_SERVER['SERVER_NAME']."/solicitud_servicios' target='_blank' >Sistema de Gesti&oacute;n de Solicitudes</a>, lo cual es indispensable para que se tramite la solicitud de compra.</div>
					     <br/>
					     <br/>
					     Por favor intente ingresar al <a href='https://".$_SERVER['SERVER_NAME']."/solicitud_servicios' target='_blank' >Sistema de Gesti&oacute;n de Solicitudes</a>, si tiene &eacute;xito vuelva a intentar crear su solicitud de material bibliogr&aacute;fico, de lo contrario comun&iacute;quese con el personal de Soporte SYRI al correo&nbsp;<img src='/biblioteca/material_bibliografico/imagenes/correo_soporte-syri.png' alt='soporte-syri' width='220' height='15'/>&nbsp;o al tel&eacute;fono 555 2334, extensi&oacute;n 8786.";
				    break;
				  case 2:
				    include "login.php";
				    echo "<br/><div class='error'>Nombre de usuario o contrase&ntilde;a incorrectos</div>";
				    break;
				  case 3:
				    include "login.php";
				    echo "<br/><div class='error'>En este momento el sistema no está disponible<br/>Por favor intente m&aacute;s tarde</div>";
				    break;
                }
              }
            }else{
			  
			  if (empty($jumi)) {
                //Esta variable es el array que usa el Mambot Jumi al incluir la página en el artículo Joomla.
				//Es poco probable que este array esté vacío, pero si lo está se redirecciona a la página de selección de formulario
				header("Location: obtencion_de_documentos.php");
				die;
              }else{
                if ($_GET['accion']=='salir'){
                  session_destroy();
                  header("Location: obtencion_de_documentos.php");
                  die;
                }
				switch($jumi[0]){
				  case "'libro'":
				    //En el POST se verifica que el formulario ya fue enviado o si es la primera vez que lo muestra
					if ($_POST['tipo'] == 'libro') {
                      //El formulario ya fue enviado, ahora se validarán sus datos
					  include_once "Validaciones.inc";
                      $validador = new Validaciones();
                      $camposError = $validador->validarCamposlibro();
                      //Si hay elementos en el array $camposError es porque se presentaron errores
                      if (count($camposError) > 0){
                        include "fm_solicitud_libros.php";
                      }else{
					    
						//Se creará el caso en Mantis con la solicitud realizada al usuario
						include("Adquisiciones.inc");
						$adquisiciones = new Adquisiciones();
						$idCasoMantis = $adquisiciones->guardarSolicitudLibro();
						if ($idCasoMantis > 0){
						  
						  //Se enviará un correo de confirmación de solicitud realizada al usuario
						  include_once("GeneradorCorreos.inc");
						  $generadorCorreos = new GeneradorCorreos();
						  if ($generadorCorreos->enviaCorreoLibro($idCasoMantis)){
						    include "correo_enviado.php";
						  }else{
                            include_once("Mantis.inc");
                            $mantis = new Mantis();
							$mantis->agregarNotaCasoMantis($idCasoMantis, "Ocurrió un error al enviar correo de confirmación al usuario");
							include "correo_error.php";
						  }
						}elseif ($idCasoMantis == -1){
						  include "mantis_error.php";
						}else{
						  include "mantis_usuario_error.php";
						}
                        //Como ya se envió la solicitud se deja en blanco la variable de sesión cantidadMaterias para que al mostrar de nuevo el formulario aparezca con sólo una fila de materias.
                        unset($_SESSION['cantidadMaterias']);
                        
                      }
				    }else{
					  //En caso de que la variable no se haya borrado aún
					  unset($_SESSION['cantidadMaterias']);
					  //El usuario va a diligenciar el formulario por primera vez
				      include "material_bibliografico/fm_solicitud_libros.php";
				    }
					break;
				  case "'audiovisual'":
				    //En el POST se verifica que el formulario ya fue enviado o si es la primera vez que lo muestra
					if ($_POST['tipo'] == 'audiovisual') {
                      //El formulario ya fue enviado, ahora se validarán sus datos
					  include_once "Validaciones.inc";
                      $validador = new Validaciones();
                      $camposError = $validador->validarCamposAudiovisual();
                      //Si hay elementos en el array $camposError es porque se presentaron errores
                      if (count($camposError) > 0){
                        include "fm_solicitud_audiovisuales.php";
                      }else{
					    
						//Se creará el caso en Mantis con la solicitud realizada al usuario
						include_once("Adquisiciones.inc");
						$adquisiciones = new Adquisiciones();
						$idCasoMantis = $adquisiciones->guardarSolicitudAudiovisual();
						if ($idCasoMantis > 0){
						  
						  //Se enviará un correo de confirmación de solicitud realizada al usuario
						  include_once("GeneradorCorreos.inc");
						  $generadorCorreos = new GeneradorCorreos();
						  if ($generadorCorreos->enviaCorreoAudiovisual($idCasoMantis)){
						    include "correo_enviado.php";
						  }else{
                            include_once("Mantis.inc");
                            $mantis = new Mantis();
                            $mantis->agregarNotaCasoMantis($idCasoMantis, "Ocurrió un error al enviar correo de confirmación al usuario");
							include "correo_error.php";
						  }
						}elseif ($idCasoMantis == -1){
						  include "mantis_error.php";
						}else{
						  include "mantis_usuario_error.php";
						}
                        //Como ya se envió la solicitud se deja en blanco la variable de sesión cantidadMaterias para que al mostrar de nuevo el formulario aparezca con sólo una fila de materias.
                        unset($_SESSION['cantidadMaterias']);
                        
					  }
				    }else{
					  //En caso de que la variable no se haya borrado aún
					  unset($_SESSION['cantidadMaterias']);
					  //El usuario va a diligenciar el formulario por primera vez
				      include "fm_solicitud_audiovisuales.php";
				    }
					break;
                  case "'caso_lectura'":
				    //En el POST se verifica que el formulario ya fue enviado o si es la primera vez que lo muestra
					if ($_POST['tipo'] == 'caso_lectura') {
                      //El formulario ya fue enviado, ahora se validarán sus datos
					  include_once "Validaciones.inc";
                      $validador = new Validaciones();
                      $camposError = $validador->validarCamposCasoLectura();
                      //Si hay elementos en el array $camposError es porque se presentaron errores
                      if (count($camposError) > 0){
                        include "fm_solicitud_casos_lecturas.php";
                      }else{
					    
                        //Se creará el caso en Mantis con la solicitud realizada al usuario
                        include_once("Adquisiciones.inc");
                        $adquisiciones = new Adquisiciones();
                        $idCasoMantis = $adquisiciones->guardarSolicitudCasoLectura();
						if ($idCasoMantis > 0){
						  //Se enviará un correo de confirmación de solicitud realizada al usuario
						  include_once("GeneradorCorreos.inc");
						  $generadorCorreos = new GeneradorCorreos();
						  if ($generadorCorreos->enviaCorreoCasoLectura($idCasoMantis)){
						    include "correo_enviado.php";
						  }else{
                            include_once("Mantis.inc");
                            $mantis = new Mantis();
                            $mantis->agregarNotaCasoMantis($idCasoMantis, "Ocurrió un error al enviar correo de confirmación al usuario");
							include "correo_error.php";
						  }
						}elseif ($idCasoMantis == -1){
						  include "mantis_error.php";
						}else{
						  include "mantis_usuario_error.php";
						}
                        //Como ya se envió la solicitud se deja en blanco la variable de sesión cantidadMaterias para que al mostrar de nuevo el formulario aparezca con sólo una fila de materias.
                        unset($_SESSION['cantidadMaterias']);
                        
					  }
				    }else{
					  //En caso de que la variable no se haya borrado aún
					  unset($_SESSION['cantidadMaterias']);
					  //El usuario va a diligenciar el formulario por primera vez
				      include "fm_solicitud_casos_lecturas.php";
				    }
					break;
				  case "'suscripcion'":
				    //En el POST se verifica que el formulario ya fue enviado o si es la primera vez que lo muestra
					if ($_POST['tipo'] == 'suscripcion') {
                      //El formulario ya fue enviado, ahora se validarán sus datos
					  include_once "Validaciones.inc";
                      $validador = new Validaciones();
                      $camposError = $validador->validarCamposSuscripcion();
                      //Si hay elementos en el array $camposError es porque se presentaron errores
                      if (count($camposError) > 0){
                        include "fm_suscripciones.php";
                      }else{
					    
						//Se creará el caso en Mantis con la solicitud realizada al usuario
                        include_once("Adquisiciones.inc");
                        $adquisiciones = new Adquisiciones();
                        $idCasoMantis = $adquisiciones->guardarSolicitudSuscripcion();
						if ($idCasoMantis > 0){
						  
						  //Se enviará un correo de confirmación de solicitud realizada al usuario
						  include_once("GeneradorCorreos.inc");
						  $generadorCorreos = new GeneradorCorreos();
						  if ($generadorCorreos->enviaCorreoSuscripcion($idCasoMantis)){
						    include "correo_enviado.php";
						  }else{
                            include_once("Mantis.inc");
                            $mantis = new Mantis();
                            $mantis->agregarNotaCasoMantis($idCasoMantis, "Ocurrió un error al enviar correo de confirmación al usuario");
                            include "correo_error.php";
						  }
						}elseif ($idCasoMantis == -1){
						  include "mantis_error.php";
						}else{
						  include "mantis_usuario_error.php";
						}
                        //Como ya se envió la solicitud se deja en blanco la variable de sesión cantidadMaterias para que al mostrar de nuevo el formulario aparezca con sólo una fila de materias.
                        unset($_SESSION['cantidadMaterias']);
                        
					  }
				    }else{
					  //En caso de que la variable no se haya borrado aún
					  unset($_SESSION['cantidadMaterias']);
					  //El usuario va a diligenciar el formulario por primera vez
				      include "fm_suscripciones.php";
				    }
					break;
				case "'articulo'":
				//En el POST se verifica que el formulario ya fue enviado o si es la primera vez que lo muestra
					if ($_POST['tipo'] == 'articulo') {
                      //El formulario ya fue enviado, ahora se validarán sus datos
					  include_once "Validaciones.inc";
                      $validador = new Validaciones();
                      $camposError = $validador->validarCamposArticulo();
                      //Si hay elementos en el array $camposError es porque se presentaron errores
                      if (count($camposError) > 0){
                        include "fm_solicitud_articulo.php";
                      }else{
					    
						//Se creará el caso en Mantis con la solicitud realizada al usuario
						include("Adquisiciones.inc");
						$adquisiciones = new Adquisiciones();
						$idCasoMantis = $adquisiciones->guardarSolicitudArticulo();
						if ($idCasoMantis > 0){
						  
						  //Se enviará un correo de confirmación de solicitud realizada al usuario
						  include_once("GeneradorCorreos.inc");
						  $generadorCorreos = new GeneradorCorreos();
						  if ($generadorCorreos->enviaCorreoArticulo($idCasoMantis)){
						    include "correo_enviado.php";
						  }else{
                            include_once("Mantis.inc");
                            $mantis = new Mantis();
							$mantis->agregarNotaCasoMantis($idCasoMantis, "Ocurrió un error al enviar correo de confirmación al usuario");
							include "correo_error.php";
						  }
						}elseif ($idCasoMantis == -1){
						  include "mantis_error.php";
						}else{
						  include "mantis_usuario_error.php";
						}
                                               
                      }
				    }else{
					  
					  //El usuario va a diligenciar el formulario por primera vez
				      include "material_bibliografico/fm_solicitud_articulo.php";
				    }
					break;
				}
              }
            }
	      ?>
	    </td>
	  </tr>
    </table>
</div>