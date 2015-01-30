<?php
//Esta clase contiene todas las funciones usadas para componer el texto de los casos en Mantis con la 
//información de los formularios de adquisición de material bibliográfico de la Biblioteca y crear el caso en Mantis

include_once('Mantis.inc');
include_once('bd_mysql.inc');

class Adquisiciones{

  /*******************************************************************************
   Nombre:     guardarSolicitudLibro
   Propósito:  Obtiene los datos ingresados en el formulario de adquisición de libros y genera el caso para la Base de Datos de Mantis.
   Entradas:   Ninguna. Los datos vienen en la sesión y del POST
   Salida:     El identificador, consecutivo, del caso que se crea en Mantis
               -1 si no se pudo crear el caso por algún error de conexión o datos
			   -2 si el solicitante no tiene usuario en Mantis para que quede como Informador
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        04-sep-09   gavarela         Creación

   Notas:
         Se usan saltos de línea y tabulaciones directamente, en lugar de usar la función chr ya que al actualizar
		 el caso de mantis, este cambia los códigos ascii usados y registra un cambio en la descripción del caso, aún si
		 el usuario no realiza cambio alguno
  ********************************************************************************/
  function guardarSolicitudLibro() {
	$reserva = 'Sí';
	if($_POST['reserva']=="no")
	  $reserva = 'No';
	
	$urgente = 'Sí';
	if($_POST['urgente']=="no")
	  $urgente = 'No';
	
	$datosSolicitud = 
'Solicitud de adquisición de libro
	                   
Datos del solicitante:
	Nombre: '.$_SESSION["nombresUsuario"].' '.$_SESSION["apellidosUsuario"].'
	Documento de identidad: '.$_SESSION['idUsuario'].'
	Correo: '.$_SESSION['correoUsuario'].'

Datos del material solicitado:
	Profesor: '.utf8_decode($_POST['profesor']).'
	Correo Profesor: '.utf8_decode($_POST['correo_profesor']).'
	Teléfono Profesor: '.utf8_decode($_POST['tel_profesor']).'
	Título: '.utf8_decode($_POST['titulo']).'
	Autor: '.utf8_decode($_POST['autor']).'
	ISBN: '.$_POST['isbn'].'
	Editorial: '.utf8_decode($_POST['editorial']).'
	Año de publicación: '.$_POST['fechaPublicacion'].'
	Edición: '.$_POST['edicion'].'
	Temas:
		'.str_replace('
', '
		', $_POST['temas']);
    
	//Se agrega la información de las materias
	$datosSolicitud .= 
'
	Materia(s) en que se usará:
';
	$contadorMaterias = 1;
    while (isset($_POST['nombreMateria'.$contadorMaterias])){
	  $datosSolicitud .= 
'		Materia '.$contadorMaterias.':
			Nombre: '.utf8_decode($_POST['nombreMateria'.$contadorMaterias]).'
			Código: '.utf8_decode($_POST['codigoMateria'.$contadorMaterias]).'
			Departamento: '.utf8_decode($_POST['departamentoMateria'.$contadorMaterias]).'
';
      $contadorMaterias++;
    }
	
	$datosSolicitud .= 
'	Departamento al que se cargará la compra: '. utf8_decode($_POST['departamento']).'
	Programa responsable de la solicitud: '. utf8_decode($_POST['programa']).'
	Es un texto guía y debe estar en reserva: '.$reserva.'
	Se necesita urgentemente: '.$urgente.'
	Cantidad requerida: '.$_POST['cantidad'].'
	Distribuidor recomendado: '.utf8_decode($_POST['distribuidor']).'
	Comentarios:
		'.str_replace('
', '
		', $_POST['comentarios']);
    
    $mantis = new Mantis();
	return $mantis->crearCasoMantis($datosSolicitud);
  }
  
  /*******************************************************************************
   Nombre:     guardarSolicitudAudiovisual
   Propósito:  Obtiene los datos ingresados en el formulario de solicitud de material audiovisual y genera el caso para la Base de Datos de Mantis.
   Entradas:   Ninguna. Los datos vienen en la sesión y del POST
   Salida:     El identificador, consecutivo, del caso que se crea en Mantis
               -1 si no se pudo crear el caso por algún error de conexión o datos
			   -2 si el solicitante no tiene usuario en Mantis para que quede como Informador
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        04-sep-09   gavarela         Creación

   Notas:
         Se usan saltos de línea y tabulaciones directamente, en lugar de usar la función chr ya que al actualizar
		 el caso de mantis, este cambia los códigos ascii usados y registra un cambio en la descripción del caso, aún si
		 el usuario no realiza cambio alguno
  ********************************************************************************/
  function guardarSolicitudAudiovisual() {
	$datosSolicitud = 
'Solicitud de adquisición de material audiovisual
	                   
Datos del solicitante:
	Nombre: '.$_SESSION["nombresUsuario"].' '.$_SESSION["apellidosUsuario"].'
	Documento de identidad: '.$_SESSION['idUsuario'].'
	Correo: '.$_SESSION['correoUsuario'].'

Datos del material solicitado:
	Profesor: '.utf8_decode($_POST['profesor']).'
	Correo Profesor: '.utf8_decode($_POST['correo_profesor']).'
	Teléfono Profesor: '.utf8_decode($_POST['tel_profesor']).'
	Título: '.utf8_decode($_POST['titulo']).'
	Tipo de material: '.utf8_decode($_POST['tipoMaterial']).'
	Temas:
		'.str_replace('
', '
		', utf8_decode($_POST['temas']));
    
	//Se agrega la información de las materias
	$datosSolicitud .= 
'
	Materia(s) en que se usará:
';
	$contadorMaterias = 1;
    while (isset($_POST['nombreMateria'.$contadorMaterias])){
	  $datosSolicitud .= 
'		Materia '.$contadorMaterias.':
			Nombre: '.utf8_decode($_POST['nombreMateria'.$contadorMaterias]).'
			Código: '.utf8_decode($_POST['codigoMateria'.$contadorMaterias]).'
			Departamento: '.utf8_decode($_POST['departamentoMateria'.$contadorMaterias]).'
';
      $contadorMaterias++;
    }
	
	$datosSolicitud .= 
'	Departamento al que se cargará la compra: '. utf8_decode($_POST['departamento']).'
	Programa responsable de la solicitud: '. utf8_decode($_POST['programa']).'
	Cantidad requerida: '.$_POST['cantidad'].'
	Distribuidor recomendado: '.utf8_decode($_POST['distribuidor']).'
	Comentarios:
		'.str_replace('
', '
		', utf8_decode($_POST['comentarios']));
    
    $mantis = new Mantis();
	return $mantis->crearCasoMantis($datosSolicitud);
  }
  
  /*******************************************************************************
   Nombre:     guardarSolicitudCasoLectura
   Propósito:  Obtiene los datos ingresados en el formulario de solicitud de casos o lecturas y genera el caso para la Base de Datos de Mantis.
   Entradas:   Ninguna. Los datos vienen en la sesión y del POST
   Salida:     El identificador, consecutivo, del caso que se crea en Mantis
               -1 si no se pudo crear el caso por algún error de conexión o datos
			   -2 si el solicitante no tiene usuario en Mantis para que quede como Informador
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        04-sep-09   gavarela         Creación

   Notas:
         Se usan saltos de línea y tabulaciones directamente, en lugar de usar la función chr ya que al actualizar
		 el caso de mantis, este cambia los códigos ascii usados y registra un cambio en la descripción del caso, aún si
		 el usuario no realiza cambio alguno
  ********************************************************************************/
  function guardarSolicitudCasoLectura() {
	$datosSolicitud = 
'Solicitud de adquisición de caso o lectura
	                   
Datos del solicitante:
	Nombre: '.$_SESSION["nombresUsuario"].' '.$_SESSION["apellidosUsuario"].'
	Documento de identidad: '.$_SESSION['idUsuario'].'
	Correo: '.$_SESSION['correoUsuario'].'

Datos del material solicitado:
	Profesor: '.utf8_decode($_POST['profesor']).'
	Correo Profesor: '.utf8_decode($_POST['correo_profesor']).'
	Teléfono Profesor: '.utf8_decode($_POST['tel_profesor']).'
	Título: '.utf8_decode($_POST['titulo']).'
	Código de la publicación: '.utf8_decode($_POST['codigo']).'
	Autor principal: '.utf8_decode($_POST['autor']).'
	Publicador: '.utf8_decode($_POST['publicador']).'
	Año de publicación: '.$_POST['fechaPublicacion'].'
	Departamento al que se cargará la compra: '. utf8_decode($_POST['departamento']).'
	Programa responsable de la solicitud: '. utf8_decode($_POST['programa']).'
	CENCO: '.$_POST['cenco'].'
	Comentarios:
		'.str_replace('
', '
		', utf8_decode($_POST['comentarios']));
    
    $mantis = new Mantis();
	return $mantis->crearCasoMantis($datosSolicitud, "caso_lectura");
  }
  
  /*******************************************************************************
   Nombre:     guardarSolicitudSuscripcion
   Propósito:  Obtiene los datos ingresados en el formulario de solicitud de suscripción y genera el caso para la Base de Datos de Mantis.
   Entradas:   Ninguna. Los datos vienen en la sesión y del POST
   Salida:     El identificador, consecutivo, del caso que se crea en Mantis
               -1 si no se pudo crear el caso por algún error de conexión o datos
			   -2 si el solicitante no tiene usuario en Mantis para que quede como Informador
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        04-sep-09   gavarela         Creación

   Notas:
         Se usan saltos de línea y tabulaciones directamente, en lugar de usar la función chr ya que al actualizar
		 el caso de mantis, este cambia los códigos ascii usados y registra un cambio en la descripción del caso, aún si
		 el usuario no realiza cambio alguno
  ********************************************************************************/
  function guardarSolicitudSuscripcion() {
	$datosSolicitud = 
'Solicitud de adquisición de suscripción
	                   
Datos del solicitante:
	Nombre: '.$_SESSION["nombresUsuario"].' '.$_SESSION["apellidosUsuario"].'
	Documento de identidad: '.$_SESSION['idUsuario'].'
	Correo: '.$_SESSION['correoUsuario'].'

Datos del material solicitado:
	Profesor: '.utf8_decode($_POST['profesor']).'
	Correo Profesor: '.utf8_decode($_POST['correo_profesor']).'
	Teléfono Profesor: '.utf8_decode($_POST['tel_profesor']).'
	Título: '.utf8_decode($_POST['titulo']).'
	ISSN: '.$_POST['issn'].'
	Editorial: '.utf8_decode($_POST['editorial']).'
	Temas:
		'.str_replace('
', '
		', utf8_decode($_POST['temas']));
    
	//Se agrega la información de las materias
	$datosSolicitud .= 
'
	Materia(s) en que se usará:
';
	$contadorMaterias = 1;
    while (isset($_POST['nombreMateria'.$contadorMaterias])){
	  $datosSolicitud .= 
'		Materia '.$contadorMaterias.':
			Nombre: '.utf8_decode($_POST['nombreMateria'.$contadorMaterias]).'
			Código: '.utf8_decode($_POST['codigoMateria'.$contadorMaterias]).'
			Departamento: '.utf8_decode($_POST['departamentoMateria'.$contadorMaterias]).'
';
      $contadorMaterias++;
    }
	
	$datosSolicitud .= 
'	Departamento al que se cargará la compra: '. utf8_decode($_POST['departamento']).'
	Programa responsable de la solicitud: '. utf8_decode($_POST['programa']).'
	Distribuidor recomendado: '.utf8_decode($_POST['distribuidor']).'
	Comentarios:
		'.str_replace('
', '
		', utf8_decode($_POST['comentarios']));
    
    $mantis = new Mantis();
	return $mantis->crearCasoMantis($datosSolicitud, "suscripcion");
  }
  
   /*******************************************************************************
   Nombre:     guardarSolicitudArtículo
   Propósito:  Obtiene los datos ingresados en el formulario de adquisición de articulos y genera el caso para la Base de Datos de Mantis.
   Entradas:   Ninguna. Los datos vienen en la sesión y del POST
   Salida:     El identificador, consecutivo, del caso que se crea en Mantis
               -1 si no se pudo crear el caso por algún error de conexión o datos
			   -2 si el solicitante no tiene usuario en Mantis para que quede como Informador
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        2012-02-06  damanzano         Creación

   Notas:
         Se usan saltos de línea y tabulaciones directamente, en lugar de usar la función chr ya que al actualizar
		 el caso de mantis, este cambia los códigos ascii usados y registra un cambio en la descripción del caso, aún si
		 el usuario no realiza cambio alguno
  ********************************************************************************/
  function guardarSolicitudArticulo() {
	
	
	$datosSolicitud = 
'Solicitud de adquisición de Artículo
	                   
Datos del solicitante:
	Nombre: '.$_SESSION["nombresUsuario"].' '.$_SESSION["apellidosUsuario"].'
	Documento de identidad: '.$_SESSION['idUsuario'].'
	Correo: '.$_SESSION['correoUsuario'].'

Datos del material solicitado:
	Profesor: '.utf8_decode($_POST['profesor']).'
	Correo Profesor: '.utf8_decode($_POST['correo_profesor']).'
	Teléfono Profesor: '.utf8_decode($_POST['tel_profesor']).'
	Título de la publicación: '.utf8_decode($_POST['titulo_pub']).'
	Título del artículo: '.utf8_decode($_POST['titulo_art']).'	
	Autor: '.utf8_decode($_POST['autor']).'
	Volumen: '.$_POST['volumen'].'
	Número: '.$_POST['numero'].'	
	Año de publicación: '.$_POST['fechaPublicacion'].'
	Páginas: '.utf8_decode($_POST['paginas']).'';
		
	
	$datosSolicitud .= 
'	Departamento al que se cargará la compra: '. utf8_decode($_POST['departamento']).'
	Programa responsable de la solicitud: '. utf8_decode($_POST['programa']).'
	CENCO: '.$_POST['cenco'].'
	Distribuidor recomendado: '.utf8_decode($_POST['distribuidor']).'
	Comentarios:
		'.str_replace('
', '
		', $_POST['comentarios']);
    
    $mantis = new Mantis();
	return $mantis->crearCasoMantis($datosSolicitud);
  }
  
  
  
  /*******************************************************************************
   Nombre:     obtenerDepartamentosAcademicos
   Propósito:  Obtiene los Departamentos Académicos que estén registrados en la Base de Datos de Mantis.
   Entradas:   Ninguna.
   Salida:     Un arreglo de string con los valores para retornar
   
   Revisiones:
   Ver        Fecha        Autor            Descripción
   ---------  -----------  ---------------  ------------------------------------
   1.0        11-FEB-2010  gavarela         Creación

   Notas:
         
  ********************************************************************************/
  function obtenerDepartamentosAcademicos() {
    $mantis = new Mantis();
	return $mantis->obtenerValoresLista(16);
  }
  
  /*******************************************************************************
   Nombre:     obtenerProgramasAcademicos
   Propósito:  Obtiene los Programas Académicos que estén registrados en la Base de Datos de Simbiosis.
   Entradas:   Ninguna.
   Salida:     Un arreglo de string con los valores para retornar
   
   Revisiones:
   Ver        Fecha        Autor            Descripción
   ---------  -----------  ---------------  ------------------------------------
   1.0        25-MAR-2010  gavarela         Creación

   Notas:
         
  ********************************************************************************/
  function obtenerProgramasAcademicos() {
    $archivo = 'lib/.config';
	$conexion = new Conexion();
	$conexion->leerarchivo($archivo);
	$conexion->conectar($conexion->usuario, $conexion->password, $conexion->db);
	$idconex = $conexion->idcone();
	
	$programasAcademicos = array();
	
	//Se obtienen los programas de pregrado
	$sql="select distinct trim(descripcion) from tbas_programas where codigo not in ('00','10') order by 1";
//	$sql="select distinct trim(fprecal_ini_may_rman(descripcion)) from tbas_programas where codigo not in ('00','10') order by 1";
	$idConsulta = $conexion->procesa($idconex, $sql);
	$resultado = OCIExecute($idConsulta, OCI_DEFAULT);
	
	$contadorProgramas = 0;
	while ($conexion->numfect($idConsulta)) {
	  $programasAcademicos[$contadorProgramas] = "".$this->capitalize($conexion->datos($idConsulta,1));
	  $contadorProgramas++;
	}

	//Se obtienen los programas de posgrado
	$sql="select distinct trim(p.nombre) from programa p where p.activo = 'S' and tipo in ( 'MAG', 'MAE', 'ESP' ) order by 1";
	$idConsulta = $conexion->procesa($idconex, $sql);
	$resultado = OCIExecute($idConsulta, OCI_DEFAULT);
	$cedulaEncargado = "";
	
	while ($conexion->numfect($idConsulta)) {
	  $programasAcademicos[$contadorProgramas] = "".$conexion->datos($idConsulta,1);
	  $contadorProgramas++;
	}
	
	$conexion->cerrar();
	return $programasAcademicos;
  }
  
  function capitalize ($cadena)
  {
      $cadena = str_replace(array("Á","É","Í","Ó","Ú","Ñ"),array("á","é","í","ó","ú","ñ"),$cadena);
      $cadena = ucwords(strtolower($cadena));
      return $cadena;
  }
}
?>