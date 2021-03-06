<?php
//Esta clase contiene todas las funciones usadas para componer el texto de los casos en Mantis con la 
//informaci�n de los formularios de adquisici�n de material bibliogr�fico de la Biblioteca y crear el caso en Mantis

include_once('Mantis.inc');
include_once('bd_mysql.inc');

class Adquisiciones{

  /*******************************************************************************
   Nombre:     guardarSolicitudLibro
   Prop�sito:  Obtiene los datos ingresados en el formulario de adquisici�n de libros y genera el caso para la Base de Datos de Mantis.
   Entradas:   Ninguna. Los datos vienen en la sesi�n y del POST
   Salida:     El identificador, consecutivo, del caso que se crea en Mantis
               -1 si no se pudo crear el caso por alg�n error de conexi�n o datos
			   -2 si el solicitante no tiene usuario en Mantis para que quede como Informador
   
   Revisiones:
   Ver        Fecha       Autor            Descripci�n
   ---------  ----------  ---------------  ------------------------------------
   1.0        04-sep-09   gavarela         Creaci�n

   Notas:
         Se usan saltos de l�nea y tabulaciones directamente, en lugar de usar la funci�n chr ya que al actualizar
		 el caso de mantis, este cambia los c�digos ascii usados y registra un cambio en la descripci�n del caso, a�n si
		 el usuario no realiza cambio alguno
  ********************************************************************************/
  function guardarSolicitudLibro() {
	$reserva = 'S�';
	if($_POST['reserva']=="no")
	  $reserva = 'No';
	
	$urgente = 'S�';
	if($_POST['urgente']=="no")
	  $urgente = 'No';
	
	$datosSolicitud = 
'Solicitud de adquisici�n de libro
	                   
Datos del solicitante:
	Nombre: '.$_SESSION["nombresUsuario"].' '.$_SESSION["apellidosUsuario"].'
	Documento de identidad: '.$_SESSION['idUsuario'].'
	Correo: '.$_SESSION['correoUsuario'].'

Datos del material solicitado:
	Profesor: '.utf8_decode($_POST['profesor']).'
	Correo Profesor: '.utf8_decode($_POST['correo_profesor']).'
	Tel�fono Profesor: '.utf8_decode($_POST['tel_profesor']).'
	T�tulo: '.utf8_decode($_POST['titulo']).'
	Autor: '.utf8_decode($_POST['autor']).'
	ISBN: '.$_POST['isbn'].'
	Editorial: '.utf8_decode($_POST['editorial']).'
	A�o de publicaci�n: '.$_POST['fechaPublicacion'].'
	Edici�n: '.$_POST['edicion'].'
	Temas:
		'.str_replace('
', '
		', $_POST['temas']);
    
	//Se agrega la informaci�n de las materias
	$datosSolicitud .= 
'
	Materia(s) en que se usar�:
';
	$contadorMaterias = 1;
    while (isset($_POST['nombreMateria'.$contadorMaterias])){
	  $datosSolicitud .= 
'		Materia '.$contadorMaterias.':
			Nombre: '.utf8_decode($_POST['nombreMateria'.$contadorMaterias]).'
			C�digo: '.utf8_decode($_POST['codigoMateria'.$contadorMaterias]).'
			Departamento: '.utf8_decode($_POST['departamentoMateria'.$contadorMaterias]).'
';
      $contadorMaterias++;
    }
	
	$datosSolicitud .= 
'	Departamento al que se cargar� la compra: '. utf8_decode($_POST['departamento']).'
	Programa responsable de la solicitud: '. utf8_decode($_POST['programa']).'
	Es un texto gu�a y debe estar en reserva: '.$reserva.'
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
   Prop�sito:  Obtiene los datos ingresados en el formulario de solicitud de material audiovisual y genera el caso para la Base de Datos de Mantis.
   Entradas:   Ninguna. Los datos vienen en la sesi�n y del POST
   Salida:     El identificador, consecutivo, del caso que se crea en Mantis
               -1 si no se pudo crear el caso por alg�n error de conexi�n o datos
			   -2 si el solicitante no tiene usuario en Mantis para que quede como Informador
   
   Revisiones:
   Ver        Fecha       Autor            Descripci�n
   ---------  ----------  ---------------  ------------------------------------
   1.0        04-sep-09   gavarela         Creaci�n

   Notas:
         Se usan saltos de l�nea y tabulaciones directamente, en lugar de usar la funci�n chr ya que al actualizar
		 el caso de mantis, este cambia los c�digos ascii usados y registra un cambio en la descripci�n del caso, a�n si
		 el usuario no realiza cambio alguno
  ********************************************************************************/
  function guardarSolicitudAudiovisual() {
	$datosSolicitud = 
'Solicitud de adquisici�n de material audiovisual
	                   
Datos del solicitante:
	Nombre: '.$_SESSION["nombresUsuario"].' '.$_SESSION["apellidosUsuario"].'
	Documento de identidad: '.$_SESSION['idUsuario'].'
	Correo: '.$_SESSION['correoUsuario'].'

Datos del material solicitado:
	Profesor: '.utf8_decode($_POST['profesor']).'
	Correo Profesor: '.utf8_decode($_POST['correo_profesor']).'
	Tel�fono Profesor: '.utf8_decode($_POST['tel_profesor']).'
	T�tulo: '.utf8_decode($_POST['titulo']).'
	Tipo de material: '.utf8_decode($_POST['tipoMaterial']).'
	Temas:
		'.str_replace('
', '
		', utf8_decode($_POST['temas']));
    
	//Se agrega la informaci�n de las materias
	$datosSolicitud .= 
'
	Materia(s) en que se usar�:
';
	$contadorMaterias = 1;
    while (isset($_POST['nombreMateria'.$contadorMaterias])){
	  $datosSolicitud .= 
'		Materia '.$contadorMaterias.':
			Nombre: '.utf8_decode($_POST['nombreMateria'.$contadorMaterias]).'
			C�digo: '.utf8_decode($_POST['codigoMateria'.$contadorMaterias]).'
			Departamento: '.utf8_decode($_POST['departamentoMateria'.$contadorMaterias]).'
';
      $contadorMaterias++;
    }
	
	$datosSolicitud .= 
'	Departamento al que se cargar� la compra: '. utf8_decode($_POST['departamento']).'
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
   Prop�sito:  Obtiene los datos ingresados en el formulario de solicitud de casos o lecturas y genera el caso para la Base de Datos de Mantis.
   Entradas:   Ninguna. Los datos vienen en la sesi�n y del POST
   Salida:     El identificador, consecutivo, del caso que se crea en Mantis
               -1 si no se pudo crear el caso por alg�n error de conexi�n o datos
			   -2 si el solicitante no tiene usuario en Mantis para que quede como Informador
   
   Revisiones:
   Ver        Fecha       Autor            Descripci�n
   ---------  ----------  ---------------  ------------------------------------
   1.0        04-sep-09   gavarela         Creaci�n

   Notas:
         Se usan saltos de l�nea y tabulaciones directamente, en lugar de usar la funci�n chr ya que al actualizar
		 el caso de mantis, este cambia los c�digos ascii usados y registra un cambio en la descripci�n del caso, a�n si
		 el usuario no realiza cambio alguno
  ********************************************************************************/
  function guardarSolicitudCasoLectura() {
	$datosSolicitud = 
'Solicitud de adquisici�n de caso o lectura
	                   
Datos del solicitante:
	Nombre: '.$_SESSION["nombresUsuario"].' '.$_SESSION["apellidosUsuario"].'
	Documento de identidad: '.$_SESSION['idUsuario'].'
	Correo: '.$_SESSION['correoUsuario'].'

Datos del material solicitado:
	Profesor: '.utf8_decode($_POST['profesor']).'
	Correo Profesor: '.utf8_decode($_POST['correo_profesor']).'
	Tel�fono Profesor: '.utf8_decode($_POST['tel_profesor']).'
	T�tulo: '.utf8_decode($_POST['titulo']).'
	C�digo de la publicaci�n: '.utf8_decode($_POST['codigo']).'
	Autor principal: '.utf8_decode($_POST['autor']).'
	Publicador: '.utf8_decode($_POST['publicador']).'
	A�o de publicaci�n: '.$_POST['fechaPublicacion'].'
	Departamento al que se cargar� la compra: '. utf8_decode($_POST['departamento']).'
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
   Prop�sito:  Obtiene los datos ingresados en el formulario de solicitud de suscripci�n y genera el caso para la Base de Datos de Mantis.
   Entradas:   Ninguna. Los datos vienen en la sesi�n y del POST
   Salida:     El identificador, consecutivo, del caso que se crea en Mantis
               -1 si no se pudo crear el caso por alg�n error de conexi�n o datos
			   -2 si el solicitante no tiene usuario en Mantis para que quede como Informador
   
   Revisiones:
   Ver        Fecha       Autor            Descripci�n
   ---------  ----------  ---------------  ------------------------------------
   1.0        04-sep-09   gavarela         Creaci�n

   Notas:
         Se usan saltos de l�nea y tabulaciones directamente, en lugar de usar la funci�n chr ya que al actualizar
		 el caso de mantis, este cambia los c�digos ascii usados y registra un cambio en la descripci�n del caso, a�n si
		 el usuario no realiza cambio alguno
  ********************************************************************************/
  function guardarSolicitudSuscripcion() {
	$datosSolicitud = 
'Solicitud de adquisici�n de suscripci�n
	                   
Datos del solicitante:
	Nombre: '.$_SESSION["nombresUsuario"].' '.$_SESSION["apellidosUsuario"].'
	Documento de identidad: '.$_SESSION['idUsuario'].'
	Correo: '.$_SESSION['correoUsuario'].'

Datos del material solicitado:
	Profesor: '.utf8_decode($_POST['profesor']).'
	Correo Profesor: '.utf8_decode($_POST['correo_profesor']).'
	Tel�fono Profesor: '.utf8_decode($_POST['tel_profesor']).'
	T�tulo: '.utf8_decode($_POST['titulo']).'
	ISSN: '.$_POST['issn'].'
	Editorial: '.utf8_decode($_POST['editorial']).'
	Temas:
		'.str_replace('
', '
		', utf8_decode($_POST['temas']));
    
	//Se agrega la informaci�n de las materias
	$datosSolicitud .= 
'
	Materia(s) en que se usar�:
';
	$contadorMaterias = 1;
    while (isset($_POST['nombreMateria'.$contadorMaterias])){
	  $datosSolicitud .= 
'		Materia '.$contadorMaterias.':
			Nombre: '.utf8_decode($_POST['nombreMateria'.$contadorMaterias]).'
			C�digo: '.utf8_decode($_POST['codigoMateria'.$contadorMaterias]).'
			Departamento: '.utf8_decode($_POST['departamentoMateria'.$contadorMaterias]).'
';
      $contadorMaterias++;
    }
	
	$datosSolicitud .= 
'	Departamento al que se cargar� la compra: '. utf8_decode($_POST['departamento']).'
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
   Nombre:     guardarSolicitudArt�culo
   Prop�sito:  Obtiene los datos ingresados en el formulario de adquisici�n de articulos y genera el caso para la Base de Datos de Mantis.
   Entradas:   Ninguna. Los datos vienen en la sesi�n y del POST
   Salida:     El identificador, consecutivo, del caso que se crea en Mantis
               -1 si no se pudo crear el caso por alg�n error de conexi�n o datos
			   -2 si el solicitante no tiene usuario en Mantis para que quede como Informador
   
   Revisiones:
   Ver        Fecha       Autor            Descripci�n
   ---------  ----------  ---------------  ------------------------------------
   1.0        2012-02-06  damanzano         Creaci�n

   Notas:
         Se usan saltos de l�nea y tabulaciones directamente, en lugar de usar la funci�n chr ya que al actualizar
		 el caso de mantis, este cambia los c�digos ascii usados y registra un cambio en la descripci�n del caso, a�n si
		 el usuario no realiza cambio alguno
  ********************************************************************************/
  function guardarSolicitudArticulo() {
	
	
	$datosSolicitud = 
'Solicitud de adquisici�n de Art�culo
	                   
Datos del solicitante:
	Nombre: '.$_SESSION["nombresUsuario"].' '.$_SESSION["apellidosUsuario"].'
	Documento de identidad: '.$_SESSION['idUsuario'].'
	Correo: '.$_SESSION['correoUsuario'].'

Datos del material solicitado:
	Profesor: '.utf8_decode($_POST['profesor']).'
	Correo Profesor: '.utf8_decode($_POST['correo_profesor']).'
	Tel�fono Profesor: '.utf8_decode($_POST['tel_profesor']).'
	T�tulo de la publicaci�n: '.utf8_decode($_POST['titulo_pub']).'
	T�tulo del art�culo: '.utf8_decode($_POST['titulo_art']).'	
	Autor: '.utf8_decode($_POST['autor']).'
	Volumen: '.$_POST['volumen'].'
	N�mero: '.$_POST['numero'].'	
	A�o de publicaci�n: '.$_POST['fechaPublicacion'].'
	P�ginas: '.utf8_decode($_POST['paginas']).'';
		
	
	$datosSolicitud .= 
'	Departamento al que se cargar� la compra: '. utf8_decode($_POST['departamento']).'
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
   Prop�sito:  Obtiene los Departamentos Acad�micos que est�n registrados en la Base de Datos de Mantis.
   Entradas:   Ninguna.
   Salida:     Un arreglo de string con los valores para retornar
   
   Revisiones:
   Ver        Fecha        Autor            Descripci�n
   ---------  -----------  ---------------  ------------------------------------
   1.0        11-FEB-2010  gavarela         Creaci�n

   Notas:
         
  ********************************************************************************/
  function obtenerDepartamentosAcademicos() {
    $mantis = new Mantis();
	return $mantis->obtenerValoresLista(16);
  }
  
  /*******************************************************************************
   Nombre:     obtenerProgramasAcademicos
   Prop�sito:  Obtiene los Programas Acad�micos que est�n registrados en la Base de Datos de Simbiosis.
   Entradas:   Ninguna.
   Salida:     Un arreglo de string con los valores para retornar
   
   Revisiones:
   Ver        Fecha        Autor            Descripci�n
   ---------  -----------  ---------------  ------------------------------------
   1.0        25-MAR-2010  gavarela         Creaci�n

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
      $cadena = str_replace(array("�","�","�","�","�","�"),array("�","�","�","�","�","�"),$cadena);
      $cadena = ucwords(strtolower($cadena));
      return $cadena;
  }
}
?>