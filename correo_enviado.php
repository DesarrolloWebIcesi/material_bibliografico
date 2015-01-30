<?php
  if (!$_SESSION['idUsuario']){
    header("Location: index.php");
    die;
  }
?>

<div id="correo_enviado">
    <p align="center">
	  La solicitud se ha realizado exitosamente y estar&aacute; sujeta a la aprobaci&oacute;n del jefe de departamento.
	  <br/>
	  <br/>
      El c&oacute;digo de su solicitud en el sistema es <b><?php echo $idCasoMantis; ?></b>
	  <br/>
	  Puede consultar la informaci&oacute;n y el estado de su solicitud en el Sistema de Gesti&oacute;n de Solicitudes: <a href="<?php echo 'https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis; ?>" target="_blank"><?php echo 'https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis; ?></a>
	  <br/>
	  <br/>
	  Se ha enviado un correo a la cuenta que tiene registrada en el sistema con los datos de su solicitud.
	</p>
	<div align="center"><a href="obtencion_de_documentos.php" title="Volver al inicio">Volver al inicio</a></div>
</div>