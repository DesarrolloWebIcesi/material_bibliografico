<?php
  if (!$_SESSION['idUsuario']){
    header("Location: index.php");
    die;
  }
?>

<div id="correo_no_enviado">
    <p align="center">
	  La solicitud se ha realizado exitosamente y estar&aacute; sujeta a la aprobaci&oacute;n del jefe de departamento.
	</p>
	<br/>
	<p align="left">
	  Sin embargo, se present&oacute; un problema al enviar un correo de confirmaci&oacute;n con los datos de su solicitud.
	  <br/>
	  El correo que est&aacute; registrado en el sistema es:<b> <?php echo $_SESSION['correoUsuario']; ?></b>
	  <br/>
	  <br/>
	  Por favor verifique que este correo sea correcto, de no serlo comun&iacute;quese con la oficina de personal para corregirlo. Una vez corregido p&oacute;ngase en contacto con la Biblioteca para que la direcci&oacute;n de su correo sea actualizada en la solicitud, para ello escriba un correo a&nbsp;<img src="images/stories/correos/procesos-bib.gif" alt="procesos-bib"/>&nbsp;citando el caso <b><?php echo $idCasoMantis; ?></b>.
	  <br/>
	  <br/>
	  Si la direcci&oacute;n es correcta aseg&uacute;rese de tener espacio en su cuenta para recibir correos y que el sistema de su proveedor de correo electr&oacute;nico est&eacute; funcionando.
	  <br/>
	  <br/>
	  Tambi&eacute;n puede consultar la informaci&oacute;n y el estado de su solicitud en el Sistema de Gesti&oacute;n de Solicitudes: <a href="<?php echo 'https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis; ?>" target="_blank"><?php echo 'https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis; ?></a>
	</p>
	<div align="center"><a href="obtencion_de_documentos.php" title="Volver al inicio">Volver al inicio</a></div>
</div>