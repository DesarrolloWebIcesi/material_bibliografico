<?php
  if (!$_SESSION['idUsuario']){
    header("Location: index.php");
    die;
  }
?>

<div id="mantis_error">
    <p align="center">
	  La solicitud <b>no</b> se pudo realizar.
	</p>
	<br/>
	Se present&oacute; un error en el sistema durante la creaci&oacute;n de la solicitud, por favor intente de nuevo.
	<br/>
	<br/>
	<br/>
	Si el error persiste, por favor comun&iacute;quese con el personal de Soporte SYRI al correo&nbsp;<img src="/biblioteca/material_bibliografico/imagenes/correo_soporte-syri.png" alt="soporte-syri" width="220" height="15"/>&nbsp;o al tel&eacute;fono 555 2334, extensi&oacute;n 8786.
	<br/>
	<br/>
	<br/>
	<div align="center"><a href="obtencion_de_documentos.php" title="Volver al inicio">Volver al inicio</a></div>
</div>