<?php
  if (!$_SESSION['idUsuario']){
    header("Location: index.php");
    die;
  }
?>

<div id="mantis_error">
    <p align="center">
	  La solicitud <b>no</b> se pudo realizar.
	  <br/>
	  <br/>
	  Al parecer usted no est&aacute; registrado en el <a href="<?php echo "https://".$_SERVER['SERVER_NAME']."/solicitud_servicios"; ?>" target="_blank" >Sistema de Gesti&oacute;n de Solicitudes</a>, lo cual es indispensable para que se tramite la solicitud de compra.
	  <br/>
	  <br/>
	  Por favor intente ingresar al <a href="<?php echo "https://".$_SERVER['SERVER_NAME']."/solicitud_servicios"; ?>" target="_blank" >Sistema de Gesti&oacute;n de Solicitudes</a>, si tiene &eacute;xito vuelva a intentar crear su solicitud de material bibliogr&aacute;fico, de lo contrario comun&iacute;quese con el personal de Soporte SYRI al correo&nbsp;<img src="/biblioteca/material_bibliografico/imagenes/correo_soporte-syri.png" alt="soporte-syri" width="220" height="15"/>&nbsp;o al tel&eacute;fono 555 2334, extensi&oacute;n 8786
	  <br/>
	</p>
	<div align="center"><a href="obtencion_de_documentos.php" title="Volver al inicio">Volver al inicio</a></div>
</div>