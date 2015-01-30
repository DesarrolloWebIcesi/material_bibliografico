<?php
//Esta clase contiene todas las funciones usadas para enviar los correos de confirmación de ingreso de solicitud de adquisición de material.
class GeneradorCorreos{
  /*******************************************************************************
   Nombre:     enviaCorreoLibro
   Propósito:  Obtiene los datos ingresados en el formulario de adquisición de libros y los envía al usuario como confirmación de ingreso de solicitud al sistema.
   Entradas:   idCasoMantis : El identificador, consecutivo, del caso que se crea en Mantis
   Salida:     true si el correo se envía exitosamente, false en caso contrario.
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        19-ago-09   gavarela         Creación

   Notas:
         
  ********************************************************************************/
  function enviaCorreoLibro($idCasoMantis){
    $para = $_SESSION['correoUsuario'];
    $asunto = 'Notificación de solicitud de adquisición';
    
	$reserva = 'S&iacute;';
	if($_POST['reserva']=="no")
	  $reserva = 'No';
	
	$urgente = 'S&iacute;';
	if($_POST['urgente']=="no")
	  $urgente = 'No';
	
    $mensaje = '
    <html>
      <head>
        <title>Notificaci&oacute;n de solicitud de adquisici&oacute;n</title>
		<style>
		  body {
		  font-family:Arial, Helvetica, sans-serif;
		  font-size:15px }
		</style>
      </head>
      <body>
        <b>Cordial saludo '.$_SESSION['nombresUsuario'].' '.$_SESSION['apellidosUsuario'].',</b>
        <br />
        <br />
        <br />
		<p>
		  Le informamos que su solicitud de adquisici&oacute;n de material bibliogr&aacute;fico ha sido registrada en nuestro sistema con el n&uacute;mero de solicitud '.$idCasoMantis.'.
		</p>
		Los datos que se recibieron en la solicitud son los siguientes:
        <table border="1" cellpadding="4" cellspacing="0">
          <tr>
            <th align="right">Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Correo Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['correo_profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Tel&eacute;fono Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['tel_profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">T&iacute;tulo</th>
			<td>'.htmlentities(utf8_decode($_POST['titulo'])).'</td>
          </tr>
          <tr>
            <th align="right">Autor</th>
			<td>'.htmlentities(utf8_decode($_POST['autor'])).'</td>
          </tr>
		  <tr>
            <th align="right">ISBN</th>
			<td>'.$_POST['isbn'].'</td>
          </tr>
		  <tr>
            <th align="right">Editorial</th>
			<td>'.htmlentities(utf8_decode($_POST['editorial'])).'</td>
          </tr>
		  <tr>
            <th align="right">A&ntilde;o de publicaci&oacute;n</th>
			<td>'.$_POST['fechaPublicacion'].'</td>
          </tr>
		   <tr>
            <th align="right">Edici&oacute;n</th>
			<td>'.htmlentities(utf8_decode($_POST['edicion'])).'</td>
          </tr>
		  <tr>
            <th align="right">Temas</th>
            <td><pre style="font-family:Arial, Helvetica, sans-serif; font-size:15px">'.htmlentities(utf8_decode($_POST['temas'])).'</pre></td>
          </tr>';
		  
		  //Se agrega la información de las materias
		  $mensaje .= '
		  <tr>
            <th align="right">Materia(s)<br /> en que se usar&aacute;</th>
			<td>
			  <table border="1" cellpadding="4" cellspacing="0" style="text-align:center"> 
			    <tr> 
                  <th>Nombre</th> 
                  <th>C&oacute;digo</th> 
                  <th>Departamento</th> 
                </tr>';
			
          $contadorMaterias = 1;
          while (isset($_POST['nombreMateria'.$contadorMaterias])){
            $mensaje .= '
                <tr>
				  <td>
				    '.htmlentities(utf8_decode($_POST['nombreMateria'.$contadorMaterias])).'
				  </td>
				  <td>
				    '.htmlentities(utf8_decode($_POST['codigoMateria'.$contadorMaterias])).'
				  </td>
				  <td>
				    '.htmlentities(utf8_decode($_POST['departamentoMateria'.$contadorMaterias])).'
				  </td>
				</tr>';
			$contadorMaterias++;
          }
		  
          $mensaje .= '
		      </table>
			</td>
		  </tr>';
		  
		  $mensaje .= '
          <tr>
            <th align="right">Departamento al que se<br/>cargar&aacute; la compra</th>
			<td>'. htmlentities(utf8_decode($_POST['departamento'])).'</td>
          </tr>
          <tr>
            <th align="right">Programa responsable<br/>de la solicitud</th>
			<td>'. htmlentities(utf8_decode($_POST['programa'])).'</td>
          </tr>
		  <tr>
            <th align="right">Es un texto gu&iacute;a<br /> y debe estar en reserva</th>
			<td>'.$reserva.'</td>
          </tr>
		  <tr>
            <th align="right">Se necesita<br /> urgentemente</th>
			<td>'.$urgente.'</td>
          </tr>
		  <tr>
            <th align="right">Cantidad requerida</th>
			<td>'.$_POST['cantidad'].'</td>
          </tr>
		  <tr>
            <th align="right">Distribuidor recomendado</th>
			<td>'.htmlentities(utf8_decode($_POST['distribuidor'])).'</td>
          </tr>
          <tr>
            <th align="right">Comentarios</th>
            <td><pre style="font-family:Arial, Helvetica, sans-serif; font-size:15px">'.htmlentities(utf8_decode($_POST['comentarios'])).'</pre></td>
          </tr>
        </table>
		<br/>
		Puede consultar la informaci&oacute;n y el estado de su solicitud en el Sistema de Gesti&oacute;n de Solicitudes: <a href="https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis.'">https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis.'</a>
		<br />
		<br />
		<br />
		<br />
		<b>
		  Biblioteca Universidad Icesi
		  <br/>
		  Direcci&oacute;n de Servicios y Recursos de Informaci&oacute;n
		  <br/>
		  Universidad Icesi
		</b>
      </body>
    </html>
    ';
    
    //Se agrega como encabezado el Content-type para que se envíe el correo como HTML
    $encabezados  = 'MIME-Version: 1.0' . "\r\n";
    $encabezados .= 'Content-type: text/html; charset=iso-8859-1' . "\r\n";
    
    //Se agrega el encabezado From para que aparezca un nombre 
    $encabezados .= 'From: Biblioteca Universidad Icesi <procesos-bib@listas.icesi.edu.co>' . "\r\n";
    
	return mail($para, $asunto, $mensaje, $encabezados);
  }
  
  /*******************************************************************************
   Nombre:     enviaCorreoAudiovisual
   Propósito:  Obtiene los datos ingresados en el formulario de adquisición de material audiovisual y los envía 
               al usuario como confirmación de ingreso de solicitud al sistema.
   Entradas:   idCasoMantis : identificador, consecutivo, del caso creado en Mantis.
   Salida:     true si el correo se envía exitosamente, false en caso contrario.
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        21-ago-09   gavarela         Creación

   Notas:
         
  ********************************************************************************/
  function enviaCorreoAudiovisual($idCasoMantis){
    $para = $_SESSION['correoUsuario'];
    $asunto = 'Notificación de solicitud de adquisición';
	
    $mensaje = '
    <html>
      <head>
        <title>Notificaci&oacute;n de solicitud de adquisici&oacute;n</title>
		<style>
		  body {
		  font-family:Arial, Helvetica, sans-serif;
		  font-size:15px }
		</style>
      </head>
      <body>
        <b>Cordial saludo '.$_SESSION['nombresUsuario'].' '.$_SESSION['apellidosUsuario'].',</b>
        <br />
        <br />
        <br />
		<p>
		  Le informamos que su solicitud de adquisici&oacute;n de material bibliogr&aacute;fico ha sido registrada en nuestro sistema con el n&uacute;mero de solicitud  '.$idCasoMantis.'.
		</p>
		Los datos que se recibieron en la solicitud son los siguientes:
        <table border="1" cellpadding="4" cellspacing="0">
          <tr>
            <th align="right">Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Correo Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['correo_profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Tel&eacute;fono Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['tel_profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">T&iacute;tulo</th>
			<td>'.htmlentities(utf8_decode($_POST['titulo'])).'</td>
          </tr>
          <tr>
            <th align="right">Tipo de material</th>
			<td>'.htmlentities(utf8_decode($_POST['tipoMaterial'])).'</td>
          </tr>
		  <tr>
            <th align="right">Temas</th>
            <td><pre style="font-family:Arial, Helvetica, sans-serif; font-size:15px">'.htmlentities(utf8_decode($_POST['temas'])).'</pre></td>
          </tr>';
		  
		  //Se agrega la información de las materias
		  $mensaje .= '
		  <tr>
            <th align="right">Materia(s)<br /> en que se usar&aacute;</th>
			<td>
			  <table border="1" cellpadding="4" cellspacing="0" style="text-align:center"> 
			    <tr> 
                  <th>Nombre</th> 
                  <th>C&oacute;digo</th> 
                  <th>Departamento</th> 
                </tr>';
			
          $contadorMaterias = 1;
          while (isset($_POST['nombreMateria'.$contadorMaterias])){
            $mensaje .= '
                <tr>
				  <td>
				    '.htmlentities(utf8_decode($_POST['nombreMateria'.$contadorMaterias])).'
				  </td>
				  <td>
				    '.htmlentities(utf8_decode($_POST['codigoMateria'.$contadorMaterias])).'
				  </td>
				  <td>
				    '.htmlentities(utf8_decode($_POST['departamentoMateria'.$contadorMaterias])).'
				  </td>
				</tr>';
			$contadorMaterias++;
          }
		  
          $mensaje .= '
		      </table>
			</td>
		  </tr>';
		  
		  $mensaje .= '
		  <tr>
            <th align="right">Departamento al que se<br/>cargar&aacute; la compra</th>
			<td>'. htmlentities(utf8_decode($_POST['departamento'])).'</td>
          </tr>
		  <tr>
            <th align="right">Programa responsable<br/>de la solicitud</td></th>
			<td>'. htmlentities(utf8_decode($_POST['programa'])).'</td>
          </tr>
		  <tr>
            <th align="right">Cantidad requerida</th>
			<td>'.htmlentities(utf8_decode($_POST['cantidad'])).'</td>
          </tr>
		  <tr>
            <th align="right">Distribuidor recomendado</th>
			<td>'.htmlentities(utf8_decode($_POST['distribuidor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Comentarios</th>
            <td><pre style="font-family:Arial, Helvetica, sans-serif; font-size:15px">'.htmlentities(utf8_decode($_POST['comentarios'])).'</pre></td>
          </tr>
        </table>
		<br/>
        Puede consultar la informaci&oacute;n y el estado de su solicitud en el Sistema de Gesti&oacute;n de Solicitudes: <a href="https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis.'">https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis.'</a>
		<br />
		<br />
		<br />
		<br />
		<b>
		  Biblioteca Universidad Icesi
		  <br/>
		  Direcci&oacute;n de Servicios y Recursos de Informaci&oacute;n
		  <br/>
		  Universidad Icesi
		</b>
      </body>
    </html>
    ';
    
    //Se agrega como encabezado el Content-type para que se envíe el correo como HTML
    $encabezados  = 'MIME-Version: 1.0' . "\r\n";
    $encabezados .= 'Content-type: text/html; charset=iso-8859-1' . "\r\n";
    
    //Se agrega el encabezado From para que aparezca un nombre 
    $encabezados .= 'From: Biblioteca Universidad Icesi <procesos-bib@listas.icesi.edu.co>' . "\r\n";
    
	return mail($para, $asunto, $mensaje, $encabezados);
  }
  
  /*******************************************************************************
   Nombre:     enviaCorreoCasoLectura
   Propósito:  Obtiene los datos ingresados en el formulario de adquisición de casos o lecturas y los envía 
               al usuario como confirmación de ingreso de solicitud al sistema.
   Entradas:   idCasoMantis : identificador, consecutivo, del caso creado en Mantis.
   Salida:     true si el correo se envía exitosamente, false en caso contrario.
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        24-ago-09   gavarela         Creación

   Notas:
         
  ********************************************************************************/
  function enviaCorreoCasoLectura($idCasoMantis){
    $para = $_SESSION['correoUsuario'];
    $asunto = 'Notificación de solicitud de adquisición';
	
    $mensaje = '
    <html>
      <head>
        <title>Notificaci&oacute;n de solicitud de adquisici&oacute;n</title>
		<style>
		  body {
		  font-family:Arial, Helvetica, sans-serif;
		  font-size:15px }
		</style>
      </head>
      <body>
        <b>Cordial saludo '.$_SESSION['nombresUsuario'].' '.$_SESSION['apellidosUsuario'].',</b>
        <br />
        <br />
        <br />
		<p>
		  Le informamos que su solicitud de adquisici&oacute;n de material bibliogr&aacute;fico ha sido registrada en nuestro sistema con el n&uacute;mero de solicitud '.$idCasoMantis.'.
		</p>
		Los datos que se recibieron en la solicitud son los siguientes:
        <table border="1" cellpadding="4" cellspacing="0">
          <tr>
            <th align="right">Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Correo Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['correo_profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Tel&eacute;fono Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['tel_profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">T&iacute;tulo</th>
			<td>'.htmlentities(utf8_decode($_POST['titulo'])).'</td>
          </tr>
          <tr>
            <th align="right">C&oacute;digo de la publicaci&oacute;n</th>
			<td>'.htmlentities(utf8_decode($_POST['codigo'])).'</td>
          </tr>
		  <tr>
            <th align="right">Autor</th>
			<td>'.htmlentities(utf8_decode($_POST['autor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Publicador</th>
			<td>'.htmlentities(utf8_decode($_POST['publicador'])).'</td>
          </tr>
		  <tr>
            <th align="right">A&ntilde;o de publicaci&oacute;n</th>
			<td>'.$_POST['fechaPublicacion'].'</td>
          </tr>
		  <tr>
            <th align="right">Departamento al que se<br/>cargar&aacute; la compra</th>
			<td>'. htmlentities(utf8_decode($_POST['departamento'])).'</td>
          </tr>
		  <tr>
            <th align="right">Programa responsable<br/>de la solicitud</td></th>
			<td>'. htmlentities(utf8_decode($_POST['programa'])).'</td>
          </tr>
		  <tr>
            <th align="right">Cenco</th>
			<td>'.$_POST['cenco'].'</td>
          </tr>
          <tr>
            <th align="right">Comentarios</th>
            <td><pre style="font-family:Arial, Helvetica, sans-serif; font-size:15px">'.htmlentities(utf8_decode($_POST['comentarios'])).'</pre></td>
          </tr>
        </table>
		<br/>
        Puede consultar la informaci&oacute;n y el estado de su solicitud en el Sistema de Gesti&oacute;n de Solicitudes: <a href="https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis.'">https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis.'</a>
		<br />
		<br />
		<br />
		<br />
		<b>
		  Biblioteca Universidad Icesi
		  <br/>
		  Direcci&oacute;n de Servicios y Recursos de Informaci&oacute;n
		  <br/>
		  Universidad Icesi
		</b>
      </body>
    </html>
    ';
    
    //Se agrega como encabezado el Content-type para que se envíe el correo como HTML
    $encabezados  = 'MIME-Version: 1.0' . "\r\n";
    $encabezados .= 'Content-type: text/html; charset=iso-8859-1' . "\r\n";
    
    //Se agrega el encabezado From para que aparezca un nombre 
    $encabezados .= 'From: Biblioteca Universidad Icesi <procesos-bib@listas.icesi.edu.co>' . "\r\n";
    
	return mail($para, $asunto, $mensaje, $encabezados);
  }
  
  /*******************************************************************************
   Nombre:     enviaCorreoSuscripcion
   Propósito:  Obtiene los datos ingresados en el formulario de adquisición de suscripciones y los envía al usuario como confirmación de ingreso de solicitud al sistema.
   Entradas:   idCasoMantis : identificador, consecutivo, del caso creado en Mantis
   Salida:     true si el correo se envía exitosamente, false en caso contrario.
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        19-ago-09   gavarela         Creación

   Notas:
         
  ********************************************************************************/
  function enviaCorreoSuscripcion($idCasoMantis){
    $para = $_SESSION['correoUsuario'];
    $asunto = 'Notificación de solicitud de adquisición';
    
	$reserva = 'S&iacute;';
	if($_POST['reserva']=="no")
	  $reserva = 'No';
	
	$urgente = 'S&iacute;';
	if($_POST['urgente']=="no")
	  $urgente = 'No';
	
    $mensaje = '
    <html>
      <head>
        <title>Notificaci&oacute;n de solicitud de adquisici&oacute;n</title>
		<style>
		  body {
		  font-family:Arial, Helvetica, sans-serif;
		  font-size:15px }
		</style>
      </head>
      <body>
        <b>Cordial saludo '.$_SESSION['nombresUsuario'].' '.$_SESSION['apellidosUsuario'].',</b>
        <br />
        <br />
        <br />
		<p>
		  Le informamos que su solicitud de adquisici&oacute;n de material bibliogr&aacute;fico ha sido registrada en nuestro sistema con el n&uacute;mero de solicitud '.$idCasoMantis.'.
		</p>
		Los datos que se recibieron en la solicitud son los siguientes:
        <table border="1" cellpadding="4" cellspacing="0">
		  <tr>
            <th align="right">Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Correo Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['correo_profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Tel&eacute;fono Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['tel_profesor'])).'</td>
          </tr>
          <tr>
            <th align="right">T&iacute;tulo</th>
			<td>'.htmlentities(utf8_decode($_POST['titulo'])).'</td>
          </tr>
		  <tr>
            <th align="right">ISSN</th>
			<td>'.$_POST['issn'].'</td>
          </tr>
		  <tr>
            <th align="right">Editorial</th>
			<td>'.htmlentities(utf8_decode($_POST['editorial'])).'</td>
          </tr>
		  <tr>
            <th align="right">Temas</th>
            <td><pre style="font-family:Arial, Helvetica, sans-serif; font-size:15px">'.htmlentities(utf8_decode($_POST['temas'])).'</pre></td>
          </tr>';
		  
		  //Se agrega la información de las materias
		  $mensaje .= '
		  <tr>
            <th align="right">Materia(s)<br /> en que se usar&aacute;</th>
			<td>
			  <table border="1" cellpadding="4" cellspacing="0" style="text-align:center"> 
			    <tr> 
                  <th>Nombre</th> 
                  <th>C&oacute;digo</th> 
                  <th>Departamento</th> 
                </tr>';
			
          $contadorMaterias = 1;
          while (isset($_POST['nombreMateria'.$contadorMaterias])){
            $mensaje .= '
                <tr>
				  <td>
				    '.htmlentities(utf8_decode($_POST['nombreMateria'.$contadorMaterias])).'
				  </td>
				  <td>
				    '.htmlentities(utf8_decode($_POST['codigoMateria'.$contadorMaterias])).'
				  </td>
				  <td>
				    '.htmlentities(utf8_decode($_POST['departamentoMateria'.$contadorMaterias])).'
				  </td>
				</tr>';
			$contadorMaterias++;
          }
		  
          $mensaje .= '
		      </table>
			</td>
		  </tr>';
		  
		  $mensaje .= '
		  <tr>
            <th align="right">Departamento al que se<br/>cargar&aacute; la compra</th>
			<td>'. htmlentities(utf8_decode($_POST['departamento'])).'</td>
          </tr>
		  <tr>
            <th align="right">Programa responsable<br/>de la solicitud</th>
			<td>'. htmlentities(utf8_decode($_POST['programa'])).'</td>
          </tr>
		  <tr>
            <th align="right">Distribuidor recomendado</th>
			<td>'.htmlentities(utf8_decode($_POST['distribuidor'])).'</td>
          </tr>
          <tr>
            <th align="right">Comentarios</th>
            <td><pre style="font-family:Arial, Helvetica, sans-serif; font-size:15px">'.htmlentities(utf8_decode($_POST['comentarios'])).'</pre></td>
          </tr>
        </table>
		<br/>
        Puede consultar la informaci&oacute;n y el estado de su solicitud en el Sistema de Gesti&oacute;n de Solicitudes: <a href="https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis.'">https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis.'</a>
		<br />
		<br />
		<br />
		<br />
		<b>
		  Biblioteca Universidad Icesi
		  <br/>
		  Direcci&oacute;n de Servicios y Recursos de Informaci&oacute;n
		  <br/>
		  Universidad Icesi
		</b>
      </body>
    </html>
    ';
    
    //Se agrega como encabezado el Content-type para que se envíe el correo como HTML
    $encabezados  = 'MIME-Version: 1.0' . "\r\n";
    $encabezados .= 'Content-type: text/html; charset=iso-8859-1' . "\r\n";
    
    //Se agrega el encabezado From para que aparezca un nombre 
    $encabezados .= 'From: Biblioteca Universidad Icesi <procesos-bib@listas.icesi.edu.co>' . "\r\n";
    
	return mail($para, $asunto, $mensaje, $encabezados);
  }
  
  /*******************************************************************************
   Nombre:     enviaCorreoArticulo
   Propósito:  Obtiene los datos ingresados en el formulario de adquisición de libros y los envía al usuario como confirmación de ingreso de solicitud al sistema.
   Entradas:   idCasoMantis : El identificador, consecutivo, del caso que se crea en Mantis
   Salida:     true si el correo se envía exitosamente, false en caso contrario.
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        2012-02-06   damanzano        Creación

   Notas:
         
  ********************************************************************************/
  function enviaCorreoArticulo($idCasoMantis){
    $para = $_SESSION['correoUsuario'];
    $asunto = 'Notificación de solicitud de adquisición';
    
		
    $mensaje = '
    <html>
      <head>
        <title>Notificaci&oacute;n de solicitud de adquisici&oacute;n</title>
		<style>
		  body {
		  font-family:Arial, Helvetica, sans-serif;
		  font-size:15px }
		</style>
      </head>
      <body>
        <b>Cordial saludo '.$_SESSION['nombresUsuario'].' '.$_SESSION['apellidosUsuario'].',</b>
        <br />
        <br />
        <br />
		<p>
		  Le informamos que su solicitud de adquisici&oacute;n de material bibliogr&aacute;fico ha sido registrada en nuestro sistema con el n&uacute;mero de solicitud '.$idCasoMantis.'.
		</p>
		Los datos que se recibieron en la solicitud son los siguientes:
        <table border="1" cellpadding="4" cellspacing="0">
          <tr>
            <th align="right">Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Correo Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['correo_profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Tel&eacute;fono Profesor</th>
			<td>'.htmlentities(utf8_decode($_POST['tel_profesor'])).'</td>
          </tr>
		  <tr>
            <th align="right">T&iacute;tulo de la Publicaci&oacute;n</th>
			<td>'.htmlentities(utf8_decode($_POST['titulo_pub'])).'</td>
          </tr>
		  <tr>
            <th align="right">T&iacute;tulo del Art&iacute;culo</th>
			<td>'.htmlentities(utf8_decode($_POST['titulo_art'])).'</td>
          </tr>
          <tr>
            <th align="right">Autor</th>
			<td>'.htmlentities(utf8_decode($_POST['autor'])).'</td>
          </tr>
		  <tr>
            <th align="right">Volumen</th>
			<td>'.$_POST['volumen'].'</td>
          </tr>
		  <tr>
            <th align="right">N&uacute;mero</th>
			<td>'.$_POST['numero'].'</td>
          </tr>
		  
		  <tr>
            <th align="right">A&ntilde;o de publicaci&oacute;n</th>
			<td>'.$_POST['fechaPublicacion'].'</td>
          </tr>
		  <tr>
            <th align="right">P&aacute;ginas</th>
			<td>'.htmlentities(utf8_decode($_POST['paginas'])).'</td>
          </tr>';
		  		  
          /*$mensaje .= '
		      </table>
			</td>
		  </tr>';*/
		  
		  $mensaje .= '
          <tr>
            <th align="right">Departamento al que se<br/>cargar&aacute; la compra</th>
			<td>'. htmlentities(utf8_decode($_POST['departamento'])).'</td>
          </tr>
          <tr>
            <th align="right">Programa responsable<br/>de la solicitud</th>
			<td>'. htmlentities(utf8_decode($_POST['programa'])).'</td>
          </tr>		  
		  <tr>
            <th align="right">Cenco</th>
			<td>'.$_POST['cenco'].'</td>
          </tr>
		  <tr>
            <th align="right">Distribuidor recomendado</th>
			<td>'.htmlentities(utf8_decode($_POST['distribuidor'])).'</td>
          </tr>
          <tr>
            <th align="right">Comentarios</th>
            <td><pre style="font-family:Arial, Helvetica, sans-serif; font-size:15px">'.htmlentities(utf8_decode($_POST['comentarios'])).'</pre></td>
          </tr>
        </table>
		<br/>
		Puede consultar la informaci&oacute;n y el estado de su solicitud en el Sistema de Gesti&oacute;n de Solicitudes: <a href="https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis.'">https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis.'</a>
		<br />
		<br />
		<br />
		<br />
		<b>
		  Biblioteca Universidad Icesi
		  <br/>
		  Direcci&oacute;n de Servicios y Recursos de Informaci&oacute;n
		  <br/>
		  Universidad Icesi
		</b>
      </body>
    </html>
    ';
    
    //Se agrega como encabezado el Content-type para que se envíe el correo como HTML
    $encabezados  = 'MIME-Version: 1.0' . "\r\n";
    $encabezados .= 'Content-type: text/html; charset=iso-8859-1' . "\r\n";
    
    //Se agrega el encabezado From para que aparezca un nombre 
    $encabezados .= 'From: Biblioteca Universidad Icesi <procesos-bib@listas.icesi.edu.co>' . "\r\n";
    
	return mail($para, $asunto, $mensaje, $encabezados);
  }
  
  /*******************************************************************************
   Nombre:     notificarEncargadoCaso
   Propósito:  Envía un correo con la información ingresada en el resumen del caso creado en Mantis al encargado de este.
   Entradas:   datosSolicitud : cadena que contiene la descripción del caso a ingresar a Mantis
               idCasoMantis : identificador, consecutivo, del caso creado en Mantis
			   correoUsuarioEncargado : correo del usuario de Mantis que está encargado del caso
   Salida:     Ninguna
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        07-sep-09   gavarela         Creación

   Notas:
         Se creó esta función ya que las librerías del propio Mantis para enviar el correo al encargado tienen demasiadas dependencias.
  ********************************************************************************/
  function notificarEncargadoCaso($idCasoMantis, $datosSolicitud, $correoUsuarioEncargado){
    $asunto = 'Nueva solicitud de adquisición recibida: '.$idCasoMantis;
    //El texto de la variable tiene saltos de línea para que el texto tenga los mismo saltos de línea
    $datosSolicitud = 'Código del caso: '.$idCasoMantis.'
https://'.$_SERVER['SERVER_NAME'].'/solicitud_servicios/view.php?id='.$idCasoMantis.'
'.$datosSolicitud;

	$encabezados = 'From: Biblioteca Universidad Icesi <procesos-bib@listas.icesi.edu.co>';
	
	mail($correoUsuarioEncargado, $asunto, $datosSolicitud, $encabezados);
  }
}