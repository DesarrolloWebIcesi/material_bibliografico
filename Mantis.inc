<?php
//Esta clase contiene todas las funciones usadas para crear los casos en Mantis con la información de los formularios de adquisición de material bibliográfico de la Biblioteca

include_once('bd_mysql.inc');
include_once('GeneradorCorreos.inc');
//Clase de conexión a Oracle
include_once("Conexion.inc");

class Mantis{
  
  private $parametrosBaseDatosMantis;
  private $idProyectoMantis;
  private $cedulaEncargadoMantis;
  private $idPrioridadMantis;
  private $idSeveridadMantis;
  private $idReproductibilidadMantis;
  private $idEstadoNuevoMantis;
  private $idEstadoAsignadoMantis;
  private $idResolucionMantis;
  private $idProyeccionMantis;
  private $idCategoriaMantis;
  private $idEtaMantis;
  private $idPerfilMantis;
  private $idEstadoVistaMantis;
  private $idSponsorMantis;
  private $idStickyMantis;
  private $areaCasoMantis;
  private $extensionUsuarioCasoMantis;
  private $ambienteDESCasoMantis;
  private $proyectoCasoMantis;
  private $tipoNotaCasoMantis;
  private $cantidadCerosHistoricoNota;
  private $medioCasoMantis;
  private $oficinaCasoMantis;
  private $tipoGestionCasoMantis;
  private $servicioBibliotecaCasoMantis;			//BIB Servicios
  private $materialesCasoMantis;					//BIB Material
  private $modoAtencionCasoMantis;
  private $serviciosOperacionalesCasoMantis; 		//DES Servicios
  private $serviciosDesarrolloCasoMantis;			//OPE Servicios
  private $causasCasoMantis;						//DES Causa
  private $departamentoAcademicoCasoMantis;			//BIB Departamentos Académicos
  private $serviciosinfraestructuraCasoMantis;		//INF Servicios
  private $aplicacionesInfraestructuraCasoMantis;	//INF Aplicaciones
  private $conectividadCasoMantis;					//INF Conectividad
  private $hardwareCasoMantis;						//INF Hardware
  private $condicionesPrestacionCasoMantis;			//Condiciones de Prestación
  private $condicionesEntregaCasoMantis;			//Condiciones de Entrega
  private $servicioProcesosCasoMantis;				//PRO Servicios
  
  /**
  *@deprecated
  *Autor:	damanzano
  *Fecha;	27-jul-10
  *Descripción:	Este atributo se reemplaza por $fechaAcordadCasoMantis y $horaAcordadaCasoMantis debido a cambios en el SGS
  */
  private $fechaHoraAcordadaCasoMantis;
  private $tiempoResolucionCasoMantis;
  private $ANSCumplidoCasoMantis;
  
  /**
  *Autor:		damanzano
  *Fecha:		27-jul-10
  *Descripción:	Estos dos atributos se agregan como reemplazo del atributio $fechaHoraAcordaCasoMantis. 
  *Este cambio se realiza debido a cambios realizados en el SGS
  */
  private $fechaAcordadaCasoMantis;
  private $horaAcordadaCasoMantis;
  
  /*******************************************************************************
   Nombre:     Cosntructor de la clase Mantis
   Propósito:  Configurar los parametros inicioales de la Clase Mantis.
   Entradas:   Ninguna.
   Salida:     Ninguna.
   
   Revisiones:
   Ver        Fecha        Autor            Descripción
   ---------  -----------  ---------------  ------------------------------------
   1.0        2009  	   gavarela         Creación
   1.1		  27-jul-10    damanzano		Modificación realizada debido a cambios en el SGS
   1.2		  03-feb-15	   cdcriollo	    Se adiciono la clausula mysql_real_escape_string al campo departamentoAcademicoCasoMantis
   Notas:
    27-jul-10	Se da valor por defecto a los nuevos atributos $fechaAcordadaCasoMantis y $horaAcordadaCasoMantis.     
  ********************************************************************************/
  public function __construct(){
    $this->parametrosBaseDatosMantis  = array("C_DB_HOST" => "mysql.icesi.edu.co",
						                      //"C_DB_NAME" => "servicios_adm",
											  "C_DB_NAME" => "sgs",
						                      "C_DB_USER" => "servicios",
						                      "C_DB_PASS" => "MfePayDghK3",
						                      "C_PORT" => "3306");
    $this->cedulaEncargadoMantis = $this->obtenerCedulaEncargadoCasoMantis();
	$this->idProyectoMantis = 14;
	$this->idPrioridadMantis = 30;
	$this->idSeveridadMantis = 10;
	$this->idReproductibilidadMantis = 10;
	$this->idEstadoNuevoMantis = 10;
	$this->idEstadoAsignadoMantis = 50;
	$this->idResolucionMantis = 10;
	$this->idProyeccionMantis = 10;
	$this->idCategoriaMantis = "";
	$this->idEtaMantis = 10;
	$this->idPerfilMantis = 0;
	$this->idEstadoVistaMantis = 50;
	$this->idSponsorMantis = 0;
	$this->idStickyMantis = 0;
	$this->areaCasoMantis = "SYRI";
	$this->extensionUsuarioCasoMantis = "N/A";
    $this->ambienteDESCasoMantis = "N/A";
    $this->tipoNotaCasoMantis = 0;
    
	//Este valor debe ser igual a $g_display_bugnote_padding en la configuración de Mantis (config_inc.php)
    $this->cantidadCerosHistoricoNota = 7;
    
    $this->medioCasoMantis = "SGS";
    $this->oficinaCasoMantis = "Biblioteca";
    $this->tipoGestionCasoMantis = "Solicitud";
    $this->servicioBibliotecaCasoMantis = "Obtención y proceso técnico de documentos";
    $this->materialesCasoMantis = array("Libros", "Material audiovisual", "Casos o lecturas", "Suscripciones");
	$this->modoAtencionCasoMantis = "N/A";
	$this->serviciosOperacionalesCasoMantis = "N/A";
	$this->serviciosDesarrolloCasoMantis = "N/A";
	$this->causasCasoMantis = "N/A";
	$this->proyectoCasoMantis = "N/A";
	$this->departamentoAcademicoCasoMantis = utf8_decode(mysql_real_escape_string($_POST['departamento']));
	$this->serviciosInfraestructuraCasoMantis = "N/A";
	$this->aplicacionesInfraestructuraCasoMantis = "N/A";
	$this->conectividadCasoMantis = "N/A";
	$this->hardwareCasoMantis = "N/A";
	$this->condicionesPrestacionCasoMantis = "N/A";
	$this->condicionesEntregaCasoMantis = "N/A";
	$this->servicioProcesosCasoMantis = "N/A";
	//$this->fechaHoraAcordadaCasoMantis = "DD-MON-AAAA HH:MM";
	$this->fechaAcordadaCasoMatis = null;
	$this->horaAcordadaCasoMantis = "HH:MM";
    $this->tiempoResolucionCasoMantis = "HH:MM";
    $this->ANSCumplidoCasoMantis = "N/A";
  }
  
  /*******************************************************************************
   Nombre:     obtenerIdUsuarioMantis
   Propósito:  Busca el ID de la Base de Datos de Mantis de un usuario, basado en la cédula de este.
   Entradas:   cedulaUsuario: La cédula se obtiene a través de la sesión
   Salida:     El identificador, consecutivo, del usuario en Mantis ó NULL si no se pudo encontrar
   
   Revisiones:
   Ver        Fecha        Autor            Descripción
   ---------  -----------  ---------------  ------------------------------------
   1.0        11-FEB-2010  gavarela         Creación

   Notas:
         
  ********************************************************************************/
  function obtenerIdUsuarioMantis($cedulaUsuario){
    $bd = new BD_mysql();
	$bd->conectar($this->parametrosBaseDatosMantis);
	
	$sql = "SELECT id FROM mantis_user_table WHERE username='".$cedulaUsuario."';";
	$resultado = $bd->ejecutarSQL($sql);
    $fila = $bd->sigRegistroArreglo($resultado, 0);
    $idUsuarioMantis = $fila['id'];
	$bd->liberarMemoria($resultado);
	$bd->cerrar();
	
	return $idUsuarioMantis;
  }
  
   /*******************************************************************************
   Nombre:     crearCasoMantis
   Propósito:  Inserta los datos ingresados en la Base de Datos de Mantis para crear el caso.
   Entradas:   datosSolicitud     : cadena que contiene la descripción del caso a ingresar a Mantis
   Salida:     El identificador, consecutivo, del caso que se crea en Mantis
               -1 si no se pudo crear el caso por algún error de conexión o datos
			   -2 si el solicitante no tiene usuario en Mantis para que quede como Informador
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        04-sep-09   gavarela         Creación
   1.1		  27-jul-10	  damanzano        Modificación necesaria para que no se envien inserten los campos N/A
   1.2		  30-jul-10   damanzano		   Se cambia el id del encargado por el id del informador en los inserts de la tabla mantis_bug_history_table	
   1.3		  11-feb-13	  jdholguin		   Se quita el reemplazo de comilla simple en el asunto del formulario para que pueda insertar correctamente en la base de datos.
   1.4        03-feb-15   cdcriollo        Se adiciono la clausula mysql_real_escape_string escapar caracteres especiales a los campos nombre_profesor, resumen caso, programa_responsable, material solicitado
                                           segun caso se soporte  172467
   Notas:
    27-jul-10	Se realiza una modificación para que no se hagan un insert de los campos personalizados que no sean necesarios (inicialmente se ingresaban como N/A).
				Esta modiciaación se realiza con el fin de modificar la aplicación cada vez que se ingrese un nuevo campo personalizado en el mantins del SGS.
				
	30-jul-10	Se realizó la maodificación en la revisón 1.2 para que en el histórico del caso quede el informador y no el encargado, como el modificador de los campos.
	12-oct-10	Se realizó una modificación para eliminar las comillas simples ingresadas por los usuarios en algunos campos.
  ********************************************************************************/
  function crearCasoMantis($datosSolicitud){
	$idInformadorMantis = $this->obtenerIdUsuarioMantis($_SESSION['idUsuario']);
	$idEncargadoMantis = $this->obtenerIdUsuarioMantis($this->cedulaEncargadoMantis);
	
	//Si el usuario encargado no está registrado en la Base de Datos de Mantis, se cancela la creación del caso.
	if (is_null($idEncargadoMantis)){
	  return -1;
	  die;
	}
	
	//Si el usuario solicitante no está registrado en la Base de Datos de Mantis, se cancela la creación del caso.
	if (is_null($idInformadorMantis)){
	  return -2;
	  die;
	}
	
	$bd = new BD_mysql();
	$bd->conectar($this->parametrosBaseDatosMantis);
	$datosSolicitud = str_replace("'","",$datosSolicitud);
	
	$sql = "INSERT INTO mantis_bug_text_table (description, steps_to_reproduce, additional_information)
	        VALUES ('".$datosSolicitud."', '', '')";
	$resultado = $bd->ejecutarSQL($sql);
	
	if($resultado){
/*	  $sql = "INSERT INTO mantis_bug_table (project_id, reporter_id, handler_id, duplicate_id, priority, severity, reproducibility, status, resolution, projection, eta, bug_text_id, profile_id, view_state, summary, sponsorship_total, sticky)
		      VALUES (%id_proyecto%, %id_informador_mantis%, %id_encargado_mantis%, 0, %id_prioridad%, %id_severidad%, %id_reproductibilidad%, %id_estado_asignado%, %id_resolucion%, %id_proyeccion%, %id_eta%, LAST_INSERT_ID(), %id_perfil%, %id_estado_vista%, '%resumen_caso%', %id_sponsor%, %id_sticky%)";
*/	  $sql = "INSERT INTO mantis_bug_table (project_id, reporter_id, handler_id, duplicate_id, priority, severity, reproducibility, status, resolution, projection, date_submitted, last_updated, eta, bug_text_id, profile_id, view_state, summary, sponsorship_total, sticky)
		      VALUES (%id_proyecto%, %id_informador_mantis%, %id_encargado_mantis%, 0, %id_prioridad%, %id_severidad%, %id_reproductibilidad%, %id_estado_asignado%, %id_resolucion%, %id_proyeccion%, UNIX_TIMESTAMP(SYSDATE()), UNIX_TIMESTAMP(SYSDATE()), %id_eta%, LAST_INSERT_ID(), %id_perfil%, %id_estado_vista%, '%resumen_caso%', %id_sponsor%, %id_sticky%)";
	  	  
	  $sql = str_replace("%id_proyecto%", $this->idProyectoMantis, $sql);
	  $sql = str_replace("%id_informador_mantis%", $idInformadorMantis, $sql);
	  $sql = str_replace("%id_encargado_mantis%", $idEncargadoMantis, $sql);
	  $sql = str_replace("%id_prioridad%", $this->idPrioridadMantis, $sql);
	  $sql = str_replace("%id_severidad%", $this->idSeveridadMantis, $sql);
	  $sql = str_replace("%id_reproductibilidad%", $this->idReproductibilidadMantis, $sql);
	  $sql = str_replace("%id_estado_asignado%", $this->idEstadoAsignadoMantis, $sql);
	  $sql = str_replace("%id_resolucion%", $this->idResolucionMantis, $sql);
	  $sql = str_replace("%id_proyeccion%", $this->idProyeccionMantis, $sql);
	  $sql = str_replace("%id_eta%", $this->idEtaMantis, $sql);
	  $sql = str_replace("%id_perfil%", $this->idPerfilMantis, $sql);
	  $sql = str_replace("%id_estado_vista%", $this->idEstadoVistaMantis, $sql);
	  $resumenCaso = substr(utf8_decode(mysql_real_escape_string($_POST['titulo'])), 0, 127);
	  //$resumenCaso = str_replace("'","\'",$resumenCaso);
	  $sql = str_replace("%resumen_caso%", $resumenCaso, $sql);
	  $sql = str_replace("%id_sponsor%", $this->idSponsorMantis, $sql);
	  $sql = str_replace("%id_sticky%", $this->idStickyMantis, $sql);
	  $resultado = $bd->ejecutarSQL($sql);
      $idCasoMantis = mysql_insert_id();
	  
      if($resultado){
        $sql = "INSERT INTO mantis_custom_field_string_table (field_id, bug_id, value)
                VALUES (5, LAST_INSERT_ID(), '%area_caso%'),
                       (2, LAST_INSERT_ID(), '%correo_usuario%'),
					   (9, LAST_INSERT_ID(), '%extension_usuario%'),
                       (25, LAST_INSERT_ID(), '%oficina%'),
					   (26, LAST_INSERT_ID(), '%tipo_gestion%'),
					   (3, LAST_INSERT_ID(), '%medio%'),                       				   
                       (19, LAST_INSERT_ID(), '%servicio_biblioteca%'),
                       (16, LAST_INSERT_ID(), '%departamento_academico%'),
					   (31, LAST_INSERT_ID(), '%programa_responsable%'),
                       (18, LAST_INSERT_ID(), '%nombre_profesor%'),
                       (17, LAST_INSERT_ID(), '%material_solicitado%')";
        
        $sql = str_replace("%area_caso%", $this->areaCasoMantis, $sql);
        $sql = str_replace("%correo_usuario%", $_SESSION['correoUsuario'], $sql);
		$sql = str_replace("%extension_usuario%", $this->extensionUsuarioCasoMantis, $sql);
        $sql = str_replace("%oficina%", $this->oficinaCasoMantis, $sql);
		$sql = str_replace("%tipo_gestion%", $this->tipoGestionCasoMantis, $sql);
        $sql = str_replace("%medio%", $this->medioCasoMantis, $sql);               
        $sql = str_replace("%servicio_biblioteca%", $this->servicioBibliotecaCasoMantis, $sql);
        $sql = str_replace("%departamento_academico%", $this->departamentoAcademicoCasoMantis, $sql);
		$sql = str_replace("%programa_responsable%", utf8_decode($_POST['programa']), $sql);
        
        $nombre_profesor = mysql_real_escape_string($_SESSION['nombresUsuario']." ".$_SESSION['apellidosUsuario']);
        $sql = str_replace("%nombre_profesor%", $nombre_profesor, $sql);
        
        $sql = str_replace("%material_solicitado%", utf8_decode($_POST['tipoSolicitud']), $sql);		
		$sql = str_replace("%hora_acordada%", $this->horaAcordadaCasoMantis, $sql);
		$sql = str_replace("%tiempo_resolucion%", $this->tiempoResolucionCasoMantis, $sql);		
        $resultado = $bd->ejecutarSQL($sql);
        
		if($resultado){
          $sql = "INSERT INTO mantis_bug_history_table (user_id, bug_id, date_modified, field_name, old_value, new_value, type)
                  VALUES (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '', '', '', 1),
                         (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '".$this->obtenerNombreCampo(5, $bd)."', '', '%area_caso%', 0),
                         (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '".$this->obtenerNombreCampo(2, $bd)."', '', '%correo_usuario%', 0),
						 (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '".$this->obtenerNombreCampo(9, $bd)."', '', '%extension_usuario%', 0),
                         (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '".$this->obtenerNombreCampo(25, $bd)."', '', '%oficina%', 0),
                         (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '".$this->obtenerNombreCampo(26, $bd)."', '', '%tipo_gestion%', 0),
						 (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '".$this->obtenerNombreCampo(3, $bd)."', '', '%medio%', 0),                         
                         (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '".$this->obtenerNombreCampo(19, $bd)."', '', '%servicio_biblioteca%', 0),
                         (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '".$this->obtenerNombreCampo(16, $bd)."', '', '%departamento_academico%', 0),
						 (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '".$this->obtenerNombreCampo(31, $bd)."', '', '%programa_responsable%', 0),
                         (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '".$this->obtenerNombreCampo(18, $bd)."', '', '%nombre_profesor%', 0),
                         (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), '".$this->obtenerNombreCampo(17, $bd)."', '', '%material_solicitado%', 0),						 
						 (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), 'status', '%id_estado_nuevo%', '%id_estado_asignado%', 0),
                         (%id_informador_mantis%, LAST_INSERT_ID(), SYSDATE(), 'handler_id', '0', '%id_encargado_mantis%', 0)";
          
          $sql = str_replace("%area_caso%", $this->areaCasoMantis, $sql);
          $sql = str_replace("%correo_usuario%", $_SESSION['correoUsuario'], $sql);
		  $sql = str_replace("%extension_usuario%", $this->extensionUsuarioCasoMantis, $sql);
          $sql = str_replace("%oficina%", $this->oficinaCasoMantis, $sql);
          $sql = str_replace("%tipo_gestion%", $this->tipoGestionCasoMantis, $sql);
		  $sql = str_replace("%medio%", $this->medioCasoMantis, $sql);          
          $sql = str_replace("%servicio_biblioteca%", $this->servicioBibliotecaCasoMantis, $sql);
          $sql = str_replace("%departamento_academico%", $this->departamentoAcademicoCasoMantis, $sql);
		  $sql = str_replace("%programa_responsable%", utf8_decode(mysql_real_escape_string($_POST['programa'])), $sql);
          $sql = str_replace("%nombre_profesor%",$nombre_profesor, $sql);
          $sql = str_replace("%material_solicitado%", utf8_decode(mysql_real_escape_string($_POST['tipoSolicitud'])), $sql);	  
          $sql = str_replace("%id_estado_nuevo%", $this->idEstadoNuevoMantis, $sql);
          $sql = str_replace("%id_estado_asignado%", $this->idEstadoAsignadoMantis, $sql);
          $sql = str_replace("%id_encargado_mantis%", $idEncargadoMantis, $sql);
		  $sql = str_replace("%id_informador_mantis%", $idInformadorMantis, $sql);
          $resultado= $bd->ejecutarSQL($sql);
        }
      }
    }
	
    if($resultado){
      //Se envía un correo al usuario de Mantis que queda encargado del caso creado
	  $sql = "SELECT email FROM mantis_user_table WHERE id=".$idEncargadoMantis;
	  $resultado = $bd->ejecutarSQL($sql);
      $fila = $bd->sigRegistroArreglo($resultado, 0);
      $correoUsuarioEncargado = $fila['email'];
	  $bd->liberarMemoria($resultado);
	  $bd->cerrar();
	  
	  $generadorCorreos = new GeneradorCorreos();
	  $generadorCorreos->notificarEncargadoCaso($idCasoMantis, $datosSolicitud, $correoUsuarioEncargado);
	  
	  return $idCasoMantis;
	}else{
      return -1;
	}
  }
  
  /*******************************************************************************
   Nombre:     agregarNotaCasoMantis
   Propósito:  Inserta los datos ingresados en la Base de Datos de Mantis para agregar una nota a un caso.
   Entradas:   idCasoMantis: identificador, consecutivo, del caso de Mantis al que se le agregará la nota.
               datosNota : cadena que contiene la nota a agregar
   Salida:     Ninguna
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        11-sep-09   gavarela         Creación

   Notas:
         
  ********************************************************************************/
  function agregarNotaCasoMantis($idCasoMantis, $datosNota){
    $idEncargadoMantis = $this->obtenerIdUsuarioMantis($this->cedulaEncargadoMantis);
	$bd = new BD_mysql();
    $bd->conectar($this->parametrosBaseDatosMantis);
    
    $sql = "INSERT INTO mantis_bugnote_text_table (note)
            VALUES ('".$datosNota."')";
    $resultado = $bd->ejecutarSQL($sql);
    
    if($resultado){
      $sql = "INSERT INTO mantis_bugnote_table (bug_id, reporter_id, bugnote_text_id, view_state, date_submitted, last_modified, note_type)
              VALUES (%id_caso%, %id_usuario_mantis%, LAST_INSERT_ID(), %id_estado_vista%, SYSDATE(), SYSDATE(), %tipo_nota%)";
      $sql = str_replace("%id_caso%", $idCasoMantis, $sql);
      $sql = str_replace("%id_usuario_mantis%", $idEncargadoMantis, $sql);
      $sql = str_replace("%id_estado_vista%", $this->idEstadoVistaMantis, $sql);
      $sql = str_replace("%tipo_nota%", $this->tipoNotaCasoMantis, $sql);
      $resultado = $bd->ejecutarSQL($sql);
      
      if($resultado){
        $sql = "INSERT INTO mantis_bug_history_table (user_id, bug_id, date_modified, field_name, old_value, new_value, type)
               VALUES (%id_usuario_mantis%, %id_caso%, SYSDATE(), '', '%id_nota%', '', 2)";
        $sql = str_replace("%id_usuario_mantis%", $idEncargadoMantis, $sql);
        $sql = str_replace("%id_caso%", $idCasoMantis, $sql);
		
		//Se agregan ceros a la izquierda del ID de la nota ya que Mantis lo hace al agregarlo en el histórico
		$idNota = str_pad(mysql_insert_id(), $this->cantidadCerosHistoricoNota, '0', STR_PAD_LEFT);
		$sql = str_replace("%id_nota%", $idNota, $sql);
        $resultado = $bd->ejecutarSQL($sql);
      }
    }
    $bd->cerrar();
  }
  
     /*******************************************************************************
   Nombre:     obtenerValoresLista
   Propósito:  Obtiene los valores de una opción que sea del tipo "ComboBox" o "Lista de Valores" de Mantis, 
               que estén registrados en la Base de Datos.
   Entradas:   idCampo: Id del campo de la Base de Datos de Mantis que tiene los valores a consultar.
   Salida:     Un arreglo de string con los valores para retornar
   
   Revisiones:
   Ver        Fecha        Autor            Descripción
   ---------  -----------  ---------------  ------------------------------------
   1.0        11-FEB-2010  gavarela         Creación

   Notas:
         
  ********************************************************************************/
  function obtenerValoresLista($idCampo) {
    $bd = new BD_mysql();
	$bd->conectar($this->parametrosBaseDatosMantis);
	
	$sql = "SELECT possible_values FROM mantis_custom_field_table WHERE id=".$idCampo;
	$resultado = $bd->ejecutarSQL($sql);
    $fila = $bd->sigRegistroArreglo($resultado, 0);
    $valoresCampo = $fila['possible_values'];
	$bd->liberarMemoria($resultado);
	$bd->cerrar();
	
	return explode('|', $valoresCampo);
  }
  
   /*******************************************************************************
   Nombre:     obtenerNombreCampo
   Propósito:  Obtiene el nombre de un campo de Mantis, según el código del campo dado
   Entradas:   codigoCampo: Código del campo de Mantis en la Base de Datos de Mantis.
               bd: un objeto para consultar la Base de Datos de Mantis.
   Salida:     Un String con el nombre del campo solicitado
   
   Revisiones:
   Ver        Fecha        Autor            Descripción
   ---------  -----------  ---------------  ------------------------------------
   1.0        17-FEB-2010  gavarela         Creación

   Notas:
         El link de la base de datos no se cierra, para que pueda seguir siendo usado.
  ********************************************************************************/
  function obtenerNombreCampo($codigoCampo, $bd) {
	$sql = "SELECT name FROM mantis_custom_field_table WHERE id=".$codigoCampo;
	$resultado = $bd->ejecutarSQL($sql);
    $fila = $bd->sigRegistroArreglo($resultado, 0);
    $nombreCampo = $fila['name'];
	$bd->liberarMemoria($resultado);
	
	return $nombreCampo;
  }
  
  /*******************************************************************************
   Nombre:     obtenerCedulaEncargadoCasoMantis
   Propósito:  Obtiene la cédula, o el nombre de usuario, registrado en TBAS_CONSTANTES del usuario que estará
               encargado de los casos creados para las solicitudes de material bibliográfico.
   Entradas:   NInguna
   Salida:     Cédula, o el nombre de usuario, el usuario que estará encargado de los casos
   
   Revisiones:
   Ver        Fecha        Autor            Descripción
   ---------  -----------  ---------------  ------------------------------------
   1.0        17-FEB-2010  gavarela         Creación

   Notas:
         El código de la constante es 175
  ********************************************************************************/
  function obtenerCedulaEncargadoCasoMantis() {
	//return '1130608864';
	//return '1130619373';
    $archivo = 'lib/.config';
	$conexion = new Conexion();
	$conexion->leerarchivo($archivo);
	$conexion->conectar($conexion->usuario, $conexion->password, $conexion->db);
	$idconex = $conexion->idcone();
	
	$sql="SELECT valor_varchar2 from TBAS_CONSTANTES WHERE codigo = 175";
	$idConsulta = $conexion->procesa($idconex, $sql);
	$resultado = OCIExecute($idConsulta, OCI_DEFAULT);
	$solicitudes = array();
	$cedulaEncargado = "";
	
	while ($conexion->numfect($idConsulta)) {
	  $cedulaEncargado = "".$conexion->datos($idConsulta,1);
	}
	
	$conexion->cerrar();
	return $cedulaEncargado;
  }
}
?>