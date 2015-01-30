<?php
//Esta clase contiene todas las funciones usadas por los formularios de adquisición de material bibliográfico de la Biblioteca para hacer sus validaciones
class Validaciones{
  /*******************************************************************************
   Nombre:     validarCamposlibro
   Propósito:  Valida los campos obligatorios del formulario de adquisición de libros del lado del servidor, en caso de que Javascript esté deshabilitado
   Entradas:   Ninguna
   Salida:     - camposError: un arreglo que contiene los mensajes de error correspondientes a cada campo validado, de forma tal que
                              cada clave es el nombre de un campo y su valor es el mensaje de error que se le muestra al usuario.
							  Ejemplo: la posición con clave titulo contiene el error del campo titulo y así sucesivamente.
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        19-ago-09   gavarela         Creación
   2.0        2012-01-2-01 damanzano       Modificación. Se agrega la validación de los campos profesor y correo profesor
   Notas:
         
  ********************************************************************************/
  function validarCamposlibro(){
    $camposError;
	if(trim($_POST['profesor']=="")){
		$camposError['profesor'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(is_numeric($_POST['profesor'])) $camposError['profesor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	}
	
	if(trim($_POST['correo_profesor']=="")){
		$camposError['correo_profesor'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(!filter_var($_POST['correo_profesor'], FILTER_VALIDATE_EMAIL)){
			$camposError['correo_profesor'] = "Este campo debe ser una direci&oacute;n de correo electr&oacute;nico v&aacute;lido";
		}
	}
	
	if(trim($_POST['titulo']) == "") $camposError['titulo'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['titulo'])) $camposError['titulo'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['autor']) == "") $camposError['autor'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['autor'])) $camposError['autor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	//Inicialmente la longitud de este código era de 10, pero desde el 1 de enero de 2007 se aumentó a 13, por lo que se encuentran ISBNs con 10 ó 13 dígitos
	//Algunos ISBN terminan en X, simbolizando el 10
	//2012-02-01 damanzano: por facilidad de uso solo se validara la logitud máxima mas no la logitud mínima
	if($_POST['isbn'] != ""){
	  if (strlen($_POST['isbn']) > 13 || strlen($_POST['isbn']) < 2) {
	    $camposError['isbn'] = "El ISBN debe ser un c&oacute;digo de m&iacute;nimo 2 y no más de 13 d&iacute;gitos";
	  }else{
	    $subcadena = substr($_POST['isbn'], 0, strlen($_POST['isbn'])-1);
        if (!is_numeric($subcadena)) {
          $camposError['isbn'] = "Los primeros d&iacute;gitos deben ser n&uacute;meros<br/>s&oacute;lo el &uacute;ltimo d&iacute;gito puede ser X";
        }else{
		  if (!is_numeric($_POST['isbn'][strlen($_POST['isbn'])-1]) && strtoupper($_POST['isbn'][strlen($_POST['isbn'])-1]) != "X") {
		    $camposError['isbn'] = "El &uacute;ltimo d&iacute;gito deber num&eacute;rico o una X";
		  }else{
		    settype($subcadena, "integer");
		    if($subcadena <= 0){
			  $camposError['isbn'] = "El ISBN debe ser mayor que cero";
			}
		  }
        }
	  }
	}
	
	if(trim($_POST['editorial']) == "") $camposError['editorial'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['editorial'])) $camposError['editorial'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if($_POST['fechaPublicacion'] == ""){
	  $camposError['fechaPublicacion'] = "Este campo no puede estar vac&iacute;o";
	}else{
	  if(!is_numeric($_POST['fechaPublicacion'])) {
	    $camposError['fechaPublicacion'] = "Este campo debe ser numérico con 4 d&iacute;gitos";
	  }else{
	    settype($_POST['fechaPublicacion'], "integer");
		if(strlen($_POST['fechaPublicacion']) != 4){
		  $camposError['fechaPublicacion'] = "Este campo debe ser num&eacute;rico con 4 d&iacute;gitos";
		}else if($_POST['fechaPublicacion'] <= 0) {
		  $camposError['fechaPublicacion'] = "El a&ntilde;o de publicaci&oacute;n debe ser mayor que cero";
		}else if($_POST['fechaPublicacion'] > date("Y")) {
		  $camposError['fechaPublicacion'] = "El a&ntilde;o de publicaci&oacute;n no puede ser mayor al a&ntilde;o actual";
		}
	  }
	}
	
	if(trim($_POST['temas']) == "") $camposError['temas'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['temas'])) $camposError['temas'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	//La siguiente repetitiva valida todos los campos de datos de las materias que el usuario haya generado para el formulario
	//Sólo se verifica que exista el campo del nombre ya que si este existe los demás también
	//por defecto el primer campo se llama nombreMateria1, es por eso que contadorMaterias arranca en 1
	$contadorMaterias = 1;
    while (isset($_POST['nombreMateria'.$contadorMaterias])){
      if(trim($_POST['nombreMateria'.$contadorMaterias]) == "")
        $camposError['nombreMateria'.$contadorMaterias] = "Este campo no puede estar vac&iacute;o";
	  
	  if(is_numeric($_POST['nombreMateria'.$contadorMaterias])) $camposError['nombreMateria'.$contadorMaterias] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	  
	  if($_POST['codigoMateria'.$contadorMaterias] != ""){
	    if(!is_numeric($_POST['codigoMateria'.$contadorMaterias])) {
          $camposError['codigoMateria'.$contadorMaterias] = "Este campo debe ser numérico";
        }else{
		  settype($_POST['codigoMateria'.$contadorMaterias], "integer");
		  if($_POST['codigoMateria'.$contadorMaterias] <= 0) {
		    $camposError['codigoMateria'.$contadorMaterias] = "El c&oacute;digo debe ser mayor que cero";
		  }
		}
	  }

	  if(trim($_POST['departamentoMateria'.$contadorMaterias]) != "") {
	    if(is_numeric($_POST['departamentoMateria'.$contadorMaterias])) 
		  $camposError['departamentoMateria'.$contadorMaterias] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	  }
	  
      $contadorMaterias++;
    }
	//El valor de las filas generadas se guarda en la sesión por si el formulario es enviado con errores y se requiere volver a mostrar las filas
	//que el usuario generó.
	$_SESSION['cantidadMaterias'] = --$contadorMaterias;
	
	if(trim($_POST['programa']) == "") $camposError['programa'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['programa'])) $camposError['programa'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['departamento']) == "") $camposError['departamento'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['departamento'])) $camposError['departamento'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if($_POST['reserva'] == "") $camposError['reserva'] = "Debe elegir un valor de la lista";
	
	if($_POST['urgente'] == "") $camposError['urgente'] = "Debe elegir un valor de la lista";
	
	if($_POST['cantidad'] == ""){
	  $camposError['cantidad'] = "Este campo no puede estar vac&iacute;o";
	}else{
	  if(!is_numeric($_POST['cantidad'])) {
        $camposError['cantidad'] = "Este campo debe ser numérico";
      }else{
	    settype($_POST['cantidad'], "integer");
	    if($_POST['cantidad'] <= 0) {
          $camposError['cantidad'] = "La cantidad solicitada debe ser mayor que cero";
        }
	  }
    }
	
	if(trim($_POST['distribuidor']) != "") {
	    if(is_numeric($_POST['distribuidor'])) 
		  $camposError['distribuidor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	}
	
	return $camposError;
  }
  
  /*******************************************************************************
   Nombre:     validarCamposAudiovisual
   Propósito:  Valida los campos obligatorios del formulario de adquisición de material audiovisual del lado del servidor, en caso de que Javascript esté deshabilitado
   Entradas:   Ninguna
   Salida:     - camposError: un arreglo que contiene los mensajes de error correspondientes a cada campo validado, de forma tal que
                              cada clave es el nombre de un campo y su valor es el mensaje de error que se le muestra al usuario.
							  Ejemplo: la posición con clave titulo contiene el error del campo titulo y así sucesivamente.
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        21-ago-09   gavarela         Creación
   2.0        2012-01-2-01 damanzano       Modificación. Se agrega la validación de los campos profesor y correo profesor
   Notas:
         
  ********************************************************************************/
  function validarCamposAudiovisual(){
    $camposError;
	
	if(trim($_POST['profesor']=="")){
		$camposError['profesor'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(is_numeric($_POST['profesor'])) $camposError['profesor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	}
	
	if(trim($_POST['correo_profesor']=="")){
		$camposError['correo_profesor'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(!filter_var($_POST['correo_profesor'], FILTER_VALIDATE_EMAIL)){
			$camposError['correo_profesor'] = "Este campo debe ser una direci&oacute;n de correo electr&oacute;nico v&aacute;lido";
		}
	}
	
	if(trim($_POST['titulo']) == "") $camposError['titulo'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['titulo'])) 
		  $camposError['titulo'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['tipoMaterial']) == "") $camposError['tipoMaterial'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['tipoMaterial'])) 
		  $camposError['tipoMaterial'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['temas']) == "") $camposError['temas'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['temas'])) 
		  $camposError['temas'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	//La siguiente repetitiva valida todos los campos de datos de las materias que el usuario haya generado para el formulario
	//Sólo se verifica que exista el campo del nombre ya que si este existe los demás también
	//por defecto el primer campo se llama nombreMateria1, es por eso que contadorMaterias arranca en 1
	$contadorMaterias = 1;
    while (isset($_POST['nombreMateria'.$contadorMaterias])){
      if(trim($_POST['nombreMateria'.$contadorMaterias]) == "")
	    $camposError['nombreMateria'.$contadorMaterias] = "Este campo no puede estar vac&iacute;o";
	  if(is_numeric($_POST['nombreMateria'.$contadorMaterias])) 
		  $camposError['nombreMateria'.$contadorMaterias] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	  
	  if($_POST['codigoMateria'.$contadorMaterias] != ""){
	    if(!is_numeric($_POST['codigoMateria'.$contadorMaterias])) {
          $camposError['codigoMateria'.$contadorMaterias] = "Este campo debe ser numérico";
        }else{
		  settype($_POST['codigoMateria'.$contadorMaterias], "integer");
		  if($_POST['codigoMateria'.$contadorMaterias] <= 0) {
		    $camposError['codigoMateria'.$contadorMaterias] = "El c&oacute;digo debe ser mayor que cero";
		  }
		}
	  }
	  
	  if(trim($_POST['departamentoMateria'.$contadorMaterias]) != ""){
	    if(is_numeric($_POST['departamentoMateria'.$contadorMaterias])) 
		  $camposError['departamentoMateria'.$contadorMaterias] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	  }
	  
      $contadorMaterias++;
    }
	//El valor de las filas generadas se guarda en la sesión por si el formulario es enviado con errores y se requiere volver a mostrar las filas
	//que el usuario generó.
	$_SESSION['cantidadMaterias'] = --$contadorMaterias;
	
	if(trim($_POST['programa']) == "") $camposError['programa'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['programa'])) 
		  $camposError['programa'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['departamento']) == "") $camposError['departamento'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['departamento'])) 
		  $camposError['departamento'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if($_POST['cantidad'] == ""){
	  $camposError['cantidad'] = "Este campo no puede estar vac&iacute;o";
	}else{
	  if(!is_numeric($_POST['cantidad'])) {
        $camposError['cantidad'] = "Este campo debe ser numérico";
      }else{
	    settype($_POST['cantidad'], "integer");
	    if($_POST['cantidad'] <= 0) {
          $camposError['cantidad'] = "La cantidad solicitada debe ser mayor que cero";
        }
	  }
    }
	
	if(trim($_POST['distribuidor']) != "") {
	    if(is_numeric($_POST['distribuidor'])) 
		  $camposError['distribuidor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	}
	
	if(trim($_POST['comentarios']) != "") {
	    if(is_numeric($_POST['comentarios'])) 
		  $camposError['comentarios'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	}
	
	return $camposError;
  }
  
  /*******************************************************************************
   Nombre:     validarCamposCasoLectura
   Propósito:  Valida los campos obligatorios del formulario de adquisición de casos o lecturas del lado del servidor, en caso de que Javascript esté deshabilitado
   Entradas:   Ninguna
   Salida:     - camposError: un arreglo que contiene los mensajes de error correspondientes a cada campo validado, de forma tal que
                              cada clave es el nombre de un campo y su valor es el mensaje de error que se le muestra al usuario.
							  Ejemplo: la posición con clave titulo contiene el error del campo titulo y así sucesivamente.
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        24-ago-09   gavarela         Creación

   Notas:
         
  ********************************************************************************/
  function validarCamposCasoLectura(){
    $camposError;
	
	if(trim($_POST['profesor']=="")){
		$camposError['profesor'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(is_numeric($_POST['profesor'])) $camposError['profesor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	}
	
	if(trim($_POST['correo_profesor']=="")){
		$camposError['correo_profesor'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(!filter_var($_POST['correo_profesor'], FILTER_VALIDATE_EMAIL)){
			$camposError['correo_profesor'] = "Este campo debe ser una direci&oacute;n de correo electr&oacute;nico v&aacute;lido";
		}
	}
	
	if(trim($_POST['titulo']) == "") $camposError['titulo'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['titulo'])) 
		  $camposError['titulo'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['autor']) == "") $camposError['autor'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['autor'])) 
		  $camposError['autor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['publicador']) == "") $camposError['publicador'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['publicador'])) 
		  $camposError['publicador'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if($_POST['fechaPublicacion'] != ""){
	  if(!is_numeric($_POST['fechaPublicacion'])) {
	    $camposError['fechaPublicacion'] = "Este campo debe ser numérico con 4 d&iacute;gitos";
	  }else{
	    settype($_POST['fechaPublicacion'], "integer");
		if(strlen($_POST['fechaPublicacion']) != 4){
		  $camposError['fechaPublicacion'] = "Este campo debe ser numérico con 4 d&iacute;gitos";
		}else if($_POST['fechaPublicacion'] <= 0) {
		  $camposError['fechaPublicacion'] = "El a&ntilde;o de publicaci&oacute;n debe ser mayor que cero";
		}else if($_POST['fechaPublicacion'] > date("Y")) {
		  $camposError['fechaPublicacion'] = "El a&ntilde;o de publicaci&oacute;n no puede ser mayor al a&ntilde;o actual";
		}
	  }
	}
	
	if(trim($_POST['programa']) == "") $camposError['programa'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['programa'])) 
		  $camposError['programa'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['departamento']) == "") $camposError['departamento'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['departamento'])) $camposError['departamento'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
		  
	if(trim($_POST['cenco']=="")){
		$camposError['cenco'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(!is_numeric($_POST['cenco'])) $camposError['cenco'] = "Este campo s&oacute;lo debe contener  n&uacute;meros";
	}
	
	return $camposError;
  }
  
  /*******************************************************************************
   Nombre:     validarCamposSuscripcion
   Propósito:  Valida los campos obligatorios del formulario de adquisición de suscripciones del lado del servidor, en caso de que Javascript esté deshabilitado
   Entradas:   Ninguna
   Salida:     - camposError: un arreglo que contiene los mensajes de error correspondientes a cada campo validado, de forma tal que
                              cada clave es el nombre de un campo y su valor es el mensaje de error que se le muestra al usuario.
							  Ejemplo: la posición con clave titulo contiene el error del campo titulo y así sucesivamente.
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        24-ago-09   gavarela         Creación

   Notas:
         
  ********************************************************************************/
  function validarCamposSuscripcion(){
    $camposError;
	
	if(trim($_POST['profesor']=="")){
		$camposError['profesor'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(is_numeric($_POST['profesor'])) $camposError['profesor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	}
	
	if(trim($_POST['correo_profesor']=="")){
		$camposError['correo_profesor'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(!filter_var($_POST['correo_profesor'], FILTER_VALIDATE_EMAIL)){
			$camposError['correo_profesor'] = "Este campo debe ser una direci&oacute;n de correo electr&oacute;nico v&aacute;lido";
		}
	}
	
	if(trim($_POST['titulo']) == "") $camposError['titulo'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['titulo'])) 
		  $camposError['titulo'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	//La longitud de este código es de 8, y en ocasiones el último dígito es una X, simbolizando el 10
	if($_POST['issn'] != ""){
	  if (strlen($_POST['issn']) < 8) {
	    $camposError['issn'] = "El ISSN debe ser un n&uacute;mero con m&aacuteximo 8 d&iacute;gitos <br/>&oacute; 7 d&iacute;gitos seguidos de X";
	  }else{
	    $subcadena = substr($_POST['issn'], 0, strlen($_POST['issn'])-2);
        if (!is_numeric($subcadena)) {
          $camposError['issn'] = "El ISSN debe ser un n&uacute;mero con m&aacuteximo 8 d&iacute;gitos <br/>&oacute; 7 d&iacute;gitos seguidos de X";
        }else{
		  if (!is_numeric($_POST['issn'][strlen($_POST['issn'])-1]) && strtoupper($_POST['issn'][strlen($_POST['issn'])-1]) != "X") {
		    $camposError['issn'] = "El ISSN debe ser un n&uacute;mero con m&aacuteximo 8 d&iacute;gitos <br/>&oacute; 7 d&iacute;gitos seguidos de X";
		  }else{
		    if($_POST['issn'] == "00000000" || strtoupper($_POST['issn']) == "0000000X"){
			  $camposError['issn'] = "El ISSN debe ser un n&uacute;mero con m&aacuteximo 8 d&iacute;gitos <br/>&oacute; 7 d&iacute;gitos seguidos de X no son v&aacute;lidos los n&uacute;meros 00000000 ni 0000000X";
			}
		  }
        }
	  }
	}
	
	if(trim($_POST['editorial']) == "") $camposError['editorial'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['editorial'])) 
		  $camposError['editorial'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['temas']) == "") $camposError['temas'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['temas'])) 
		  $camposError['temas'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	//La siguiente repetitiva valida todos los campos de datos de las materias que el usuario haya generado para el formulario
	//Sólo se verifica que exista el campo del nombre ya que si este existe los demás también
	//por defecto el primer campo se llama nombreMateria1, es por eso que contadorMaterias arranca en 1
	$contadorMaterias = 1;
    while (isset($_POST['nombreMateria'.$contadorMaterias])){
      if(trim($_POST['nombreMateria'.$contadorMaterias]) == "") $camposError['nombreMateria'.$contadorMaterias] = "Este campo no puede estar vac&iacute;o";
	  if(is_numeric($_POST['nombreMateria'.$contadorMaterias])) 
		  $camposError['nombreMateria'.$contadorMaterias] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	  
	  if($_POST['codigoMateria'.$contadorMaterias] != ""){
	    if(!is_numeric($_POST['codigoMateria'.$contadorMaterias])) {
          $camposError['codigoMateria'.$contadorMaterias] = "Este campo debe ser numérico";
        }else{
		  settype($_POST['codigoMateria'.$contadorMaterias], "integer");
		  if($_POST['codigoMateria'.$contadorMaterias] <= 0) {
		    $camposError['codigoMateria'.$contadorMaterias] = "El c&oacute;digo debe ser mayor que cero";
		  }
		}
	  }
	  
	  if(trim($_POST['departamentoMateria'.$contadorMaterias]) != ""){
	    if(is_numeric($_POST['departamentoMateria'.$contadorMaterias])) 
		  $camposError['departamentoMateria'.$contadorMaterias] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	  }
	  
      $contadorMaterias++;
    }
	//El valor de las filas generadas se guarda en la sesión por si el formulario es enviado con errores y se requiere volver a mostrar las filas
	//que el usuario generó.
	$_SESSION['cantidadMaterias'] = --$contadorMaterias;
	
	if(trim($_POST['programa']) == "") $camposError['programa'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['programa'])) 
		  $camposError['programa'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['departamento']) == "") $camposError['departamento'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['departamento'])) 
		  $camposError['departamento'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['distribuidor']) != "") {
	    if(is_numeric($_POST['distribuidor'])) 
		  $camposError['distribuidor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	}
	
	return $camposError;
  }
  
  /*******************************************************************************
   Nombre:     validarCamposArticulo
   Propósito:  Valida los campos obligatorios del formulario de adquisición de artículos del lado del servidor, en caso de que Javascript esté deshabilitado
   Entradas:   Ninguna
   Salida:     - camposError: un arreglo que contiene los mensajes de error correspondientes a cada campo validado, de forma tal que
                              cada clave es el nombre de un campo y su valor es el mensaje de error que se le muestra al usuario.
							  Ejemplo: la posición con clave titulo contiene el error del campo titulo y así sucesivamente.
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        2012-01-2-01 damanzano       Creación.
   Notas:
         
  ********************************************************************************/
  function validarCamposArticulo(){
    $camposError;
	if(trim($_POST['profesor']=="")){
		$camposError['profesor'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(is_numeric($_POST['profesor'])) $camposError['profesor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	}
	
	if(trim($_POST['correo_profesor']=="")){
		$camposError['correo_profesor'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(!filter_var($_POST['correo_profesor'], FILTER_VALIDATE_EMAIL)){
			$camposError['correo_profesor'] = "Este campo debe ser una direci&oacute;n de correo electr&oacute;nico v&aacute;lido";
		}
	}
	
	if(trim($_POST['titulo_pub']) == "") $camposError['titulo_pub'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['titulo_pub'])) $camposError['titulo_pub'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['titulo_art']) == "") $camposError['titulo_art'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['titulo_art'])) $camposError['titulo_art'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['autor']) == "") $camposError['autor'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['autor'])) $camposError['autor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['volumen']!="")){
		if(!is_numeric($_POST['volumen'])) $camposError['volumen'] = "Este campo s&oacute;lo debe contener  n&uacute;meros";
	}
	
	if(trim($_POST['numero']!="")){
		if(!is_numeric($_POST['numero'])) $camposError['numero'] = "Este campo s&oacute;lo debe contener  n&uacute;meros";
	}
				
	if($_POST['fechaPublicacion'] == ""){
	  $camposError['fechaPublicacion'] = "Este campo no puede estar vac&iacute;o";
	}else{
	  if(!is_numeric($_POST['fechaPublicacion'])) {
	    $camposError['fechaPublicacion'] = "Este campo debe ser numérico con 4 d&iacute;gitos";
	  }else{
	    settype($_POST['fechaPublicacion'], "integer");
		if(strlen($_POST['fechaPublicacion']) != 4){
		  $camposError['fechaPublicacion'] = "Este campo debe ser numérico con 4 d&iacute;gitos";
		}else if($_POST['fechaPublicacion'] <= 0) {
		  $camposError['fechaPublicacion'] = "El a&ntilde;o de publicaci&oacute;n debe ser mayor que cero";
		}else if($_POST['fechaPublicacion'] > date("Y")) {
		  $camposError['fechaPublicacion'] = "El a&ntilde;o de publicaci&oacute;n no puede ser mayor al a&ntilde;o actual";
		}
	  }
	}
		
	if(trim($_POST['programa']) == "") $camposError['programa'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['programa'])) $camposError['programa'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
	if(trim($_POST['departamento']) == "") $camposError['departamento'] = "Este campo no puede estar vac&iacute;o";
	if(is_numeric($_POST['departamento'])) $camposError['departamento'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	
		
	if(trim($_POST['distribuidor']) != "") {
	    if(is_numeric($_POST['distribuidor'])) 
		  $camposError['distribuidor'] = "Este campo no puede tener s&oacute;lo n&uacute;meros";
	}
	
	if(trim($_POST['cenco']=="")){
		$camposError['cenco'] = "Este campo no puede estar vac&iacute;o";
	}else{
		if(!is_numeric($_POST['cenco'])) $camposError['cenco'] = "Este campo s&oacute;lo debe contener  n&uacute;meros";
	}
	
	return $camposError;
  }
  
  
}