<?php

class BD_mysql {

	/**
	* Nombre de su servidor PostgreSQL
	* @var string
	*/
    var $_servidor      = "";    
	/**
	* Nombre de la base de datos en ese servidor
	* @var string
	*/
    var $_base_datos     = "";    
	/**
	* Usuario de la base de datos
	* @var string
	*/
    var $_usuario       = "";    
	/**
	* Clave del usuario de la base de datos
	* @var string
	*/
    var $_clave         = "";    
	/**
	* Identificador de la conexion
	* @var string
	*/
    var $_id_conexion   = 0;     
	/**
	* Cadena de error
	* @var string
	*/
    var $_error         = "";    


	/**
	* Determina si hay una transaccion activa
	* @var boolean
	*/
    var $_hayTransaccionActiva   = "";    


    /**
     * Constructor de la clase
     * 
     */
    function BD_mysql ()
    {	//print "BD_mysql.constructor<br>";
        $this->_servidor  = ""; //Servidor Predeterminado
        $this->_base_datos = ""; //Base de Datos Predeterminada
        $this->_usuario   = ""; //Usuario Predeterminado
        $this->_clave     = ""; //Clave Predeterminada
        $this->_protocolo = ""; //Protocolo de conexiOn
        $this->_puerto    = "";     //Puerto de conexiOn
        $this->_id_conexion = 0;          
        $this->_error       = "";
		$this->_hayTransaccionActiva = false;
    }// END function BD_pgsql

    
    /**
     * Permite la conexion a un servidor
     * 
     */
    function conectar ($parametros_conexion)
    {
       	$this->establecerDatosConexion ($parametros_conexion);        
        $parametros = "";
        $servidor = $this->_servidor;
		// Si el protocolo escogido es TCP, se debe habilitar el Postmaster para que dE este soporte
        // lo recomendado es usar Unix Socket
        if (strtolower($this->_protocolo) == 'tcp') {
            if ($this->_servidor != "" && $this->_puerto != "" ) {
                $parametros .= " host=".$this->_servidor;
                $parametros .= " port=".$this->_puerto;
				$servidor = $this->_servidor.":".$this->_puerto;
            }  
        }
        $tmp = array ();
        if($this->_id_conexion == 0) {
            if ($this->_base_datos != "") {
                $parametros .= " dbname=".$this->_base_datos;

                if ($this->_usuario != "" && $this->_clave != "") { 
                    $parametros .= " user=".$this->_usuario;
                    $parametros .= " password=".$this->_clave;
                }
                $this->_id_conexion = mysql_connect($servidor,$this->_usuario,$this->_clave);
                if (!$this->_id_conexion){
                    $this->mostrarError("Conexi&oacute;n Fallida:<br>\n id_conexion == false");
                }
                else {
		            if (!mysql_select_db($this->_base_datos, $this->_id_conexion)) {
						$this->mostrarError("Seleccion de bd Fallida:<br>\n".mysql_error($this->_id_conexion));
            		}
                }
            }
            else {
                $this->mostrarError("No se especific&oacute; una base de datos para la conexi&oacute;n con MySQL\n");
            }
        }
    }// END function conectar


    /**
     * Se encarga de cerrar la conexion con la base de datos
     * 
     */
    function cerrar ()
    {
        if($this->_id_conexion != 0){
			$ret = mysql_close($this->_id_conexion);
            $this->_id_conexion = 0;
            return $ret;
        } 
    }// END function cerrar


    /**
     * Se encarga de desplegar los mensajes de error
     * 
     */
    function mostrarError ($msg)
    {
        print "<br><br><B>Error:</B> $msg<BR>\n";
        die("Sesion Detenida.");
    }// END function mostrarError


    /**
     * Se encarga de enviar sentencias SQL
     * 
     */
    function ejecutarSQL ($sentenciaSQL)
    {
        $id_sql = @mysql_query($sentenciaSQL,$this->_id_conexion);
		$this->_error = mysql_error($this->_id_conexion);
        if (!$id_sql){
            $this->mostrarError("SQL Inv&aacute;lido: ".$sentenciaSQL."\n".$this->_error);
        }
        return $id_sql;
    }// END function ejecutarSQL

	
    /**
     * Metodo iniciarTransaccion
     * Inicia una transacci&oacute;n en modo encadenado, OJO mirar documentaci&oacute;n
	 *
	 * Las versiones 3.23.x tienen soporte para transacciones unicamente con tablas
	 * de tipo InnoDB, es decir, para usar las transacciones la tabla debe ser de 
	 * este tipo.
	 *
	 * Ejemplo de tabla InnoDB:
	 *
	 * CREATE TABLE nomTabla ( atr int ) TYPE = INNODB;
	 *
     */
    function iniciarTransaccion ()
    {
	
		if ( !$this->_hayTransaccionActiva ) {
        	mysql_query('SET AUTOCOMMIT=0', $this->_id_conexion);
        	mysql_query('BEGIN', $this->_id_conexion);
			$this->_hayTransaccionActiva = true;
		}

        return ; 
    }// END function iniciarTransaccion


    /**
     * Metodo confirmarTransaccion
     * Confirma la transacci&oacute;n actual, OJO
	 *
	 * Las versiones 3.23.x tienen soporte para transacciones unicamente con tablas
	 * de tipo InnoDB, es decir, para usar las transacciones la tabla debe ser de 
	 * este tipo.
	 *
	 * Ejemplo de tabla InnoDB:
	 *
	 * CREATE TABLE nomTabla ( atr int ) TYPE = INNODB;
	 *

     */
    function confirmarTransaccion ()
    {
		if ( $this->_hayTransaccionActiva ) {
			mysql_query('COMMIT', $this->_id_conexion);
    	    mysql_query('SET AUTOCOMMIT=1', $this->_id_conexion);
			$this->_hayTransaccionActiva = false;
		}

        return ;
    }// END function confirmarTransaccion


    /**
     * Metodo abortarTransaccion
     * Aborta la transacci&oacute;n actual, es un alias de: roolback
	 *
	 * Las versiones 3.23.x tienen soporte para transacciones unicamente con tablas
	 * de tipo InnoDB, es decir, para usar las transacciones la tabla debe ser de 
	 * este tipo.
	 *
	 * Ejemplo de tabla InnoDB:
	 *
	 * CREATE TABLE nomTabla ( atr int ) TYPE = INNODB;
	 *

     */
    function abortarTransaccion ()
    {
		if ( $this->_hayTransaccionActiva ) {
			mysql_query('ROLLBACK', $this->_id_conexion);
    	    mysql_query('SET AUTOCOMMIT=1', $this->_id_conexion);
			$this->_hayTransaccionActiva = false;
		}
        return ;
    }// END function abortarTransaccion


    /**
     * Metodo establecerDatosConexion
     * Se encarga de asignar los valores de los datos de conexi&oacute;n a las variables de la clase
     * Par&aacute;metros:
     *     $parametros_conexion     arreglo asociativo con los parAmetros de la conexiOn
     */
    function establecerDatosConexion ($parametros_conexion)
    {
    	$this->_servidor   = $parametros_conexion['C_DB_HOST']; 
        $this->_base_datos = $parametros_conexion['C_DB_NAME']; 
        $this->_usuario    = $parametros_conexion['C_DB_USER'];  
        $this->_clave      = $parametros_conexion['C_DB_PASS'];  
        $this->_protocolo  = $parametros_conexion['C_PROTOCOL'];  
        $this->_puerto     = $parametros_conexion['C_PORT'];  
    }// END function establecerDatosConexion


     /**
     * Retorna el siguiente registro de una consulta como un arreglo
     * 
     */
    function sigRegistroArreglo ($id_sql,$fila)
    {
        if ($fila !== null) {
            if (!@mysql_data_seek($id_sql, $fila)) {
                return false;
            }
        }
        $registro = mysql_fetch_array($id_sql, MYSQL_BOTH);
        return $registro;
    }// END function sigRegistroArreglo


     /**
     * Retorna el siguiente registro de una consulta como un objeto
     * 
     */
    function sigRegistroObjeto ($id_sql,$fila)
    {
        $object = mysql_fetch_object($id_sql,MYSQL_BOTH);
        return $object;
    }// END function sigRegistroObjeto

	
    /**
     * Retorna el numero de filas o registros de una consulta
     *
     */
    function numFilas ($id_sql)
    {
        if($id_sql !=0){
            return mysql_num_rows($id_sql);
        }
        return 0;    
    }// END function numFilas
 

    /**
     * Se retornar el n&uacute;mero de filas afectadas de las operaciones: INSERT, DELETE y UPDATE
     * 
     */
    function filasAfectadas ($id_sql)
    {
        $numFilasAfectadas=mysql_affected_rows(/*$id_sql*/$this->_id_conexion);
        return $numFilasAfectadas;
    }// END function filasAfectadas


    /**
     * Se debe retornar el nombre de un atributo
     *
     */
    function obtenerNombreAtributo ($id_sql,$j)
    {
        return mysql_field_name($id_sql,$j);
    }// END function obtenerNombreAtributo


    /**
     * Retorna el n&uacute;mero de atributos de una consulta
     *   
     */
    function numeroDeAtributos ($id_sql)
    {
        return mysql_num_fields($id_sql);
    }// END function numeroDeAtributos


    /**
     * Se encarga de liberar la memoria utilizada por una consulta
     *
     */
    function liberarMemoria ($id_sql)
    {
        mysql_free_result($id_sql);
    }// END function liberarMemoria


}// END class BD_pgsql
?>
