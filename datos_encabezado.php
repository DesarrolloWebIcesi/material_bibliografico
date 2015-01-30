<link rel="stylesheet" media="all" type="text/css" href="material_bibliografico/css_formularios.css" />
<script type="text/javascript">
//Refresca la página cada 20 minutos y tres segundos
function timedRefresh(timeoutPeriod) {
	setTimeout("location.reload(true);",timeoutPeriod);
}
timedRefresh(1200003);
</script>
<?php 
  session_start();
  //La sesión se destruye y se envía a la página de inicio cada 20 minutos si no hay actividad
  $maximoInactivo = 1200;
  if(isset($_SESSION['ultimoAcceso']) && isset($_SESSION['idUsuario']) ) {
	$tiempoUltimoAcceso = time() - $_SESSION['ultimoAcceso'];
	if($tiempoUltimoAcceso >= $maximoInactivo){
      session_destroy();
      header("Location: obtencion_de_documentos.php");
	}
  }
  $_SESSION['ultimoAcceso'] = time();
  
  //Si hay datos en la sesión el usuario ya se logueó, entonces se muestran sus datos y la opción salir encima del contenido
  //No importa la URL del artículo de Joomla, que corresponda a un formulario de adquisiciones, que se use para salir
  //Cuando invoque al index y vea el parámetro salir, se borrará la sesión
  if ($_SESSION['idUsuario']){
?>
    <table align="right">
	  <tr class='autenticado'>
	    <td>
          Ha ingresado como <?php echo $_SESSION['nombresUsuario']." ".$_SESSION['apellidosUsuario']; ?>
          <br/>
		  Correo: <?php echo $_SESSION['correoUsuario']; ?>
		  <br/>
          <a href='obtencion_de_documentos.php' title='Volver al inicio'>Volver al inicio</a>
          <br/>
		  <br/>
          <a href='adquisicion_audiovisual.php?accion=salir' title='Salir'>Salir</a>
        </td>
      </tr>
	</table>
	<br/>
	<br/>
<?php
  }
?>