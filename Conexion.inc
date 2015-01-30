<?php

	
	
	/**
    *clase Conexion
    *
    *Clase encargada de hacer la conexion con una base de datos oracle y MSQL.
    *@package class
    *@author Blanca Gómez Muñoz
    *@version $Id: Conexion.php 03
	*@since creación: 2008-08-19 Fecha modificación:2009-11-17
    */
	class Conexion
	{
	
	// VARIABLES PARA CONFIGURAR LA CONEXION
	var $servidor= "localhost";
	
	/**
	*bogomez – Blanca Gómez Muñoz
	*2008-08-19
	*Descomentar la siguiente linea si la conexion es para un manejador de BD MYSQL y comentar la posterior a esta.
	*
	*/
	//var $basedatos = "MySQL";
	var $basedatos = "oracle";
	
	var $filas=array(); // Es una array enumerado que contiene una fila extraida de $resultado
	
	var $numcols; // Guarda el número de columnas que tiene el resultado de una consulta.
	
	var $nomcols = array(); // Array que contiene los nombres de las columnas ordenados por posición desde 0.
	
	var $tipocols = array(); // Array que contiene los tipos de columnas String , number , text ...
	
	var $tamcols = array(); // Array que contiene la longuitud de las columnas , 20 , 30 ,
	
	var $numfilas; // Guarda el número de filas que devuelve el resultado de una consulta.
	
	
	/**
	*bogomez – Blanca Gómez Muñoz
	*2008-08-19
	*Esta variable guarda el identificador de conexón que devuelven las funciones de conexión.
	*
	*/
	var $id=0; 
	/* ($this->id=mysql_connect($server,$user,$pass) por ejemplo) */
	
	
	/**
	*bogomez – Blanca Gómez Muñoz
	*2008-08-19
	*Guarda identidicador de un conjunto de datos resultante de la ejecución de una consulta
	*De este conjunto de datos tenemos que extraer las filas.
	*
	*/
	var $resultado;
	
	var $fila_actual; // Usada para saber que fila tiene que actualizar una sentencia update.
	
	var $ultima_consulta;
	
	var $vistas;
	
	/**
	*Class constructor.
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   
	*@return  
	*/
	public function  Conexion()
	{
	
	}#f_conectar
	
	
	/**
	*@method  conectar($usuario=" ", $password=" ", $db=" ") .Siempre se ejecuta cuando se instancia,
	* la clase ($objeto = new Conexion; por ejemplo)
	* utiliza las variables globales $servidor,$usuario,$password y $db para conectar, sus valores estan deifnidos
	* en la zona de declaraciones y toma los valores del archivo plano que almacena los datos de conexion.
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@see     OCILogon($this->usuario,$this->password,$this->db)
	*@param   
	*@return  
	*/
	function conectar($usuario=" ", $password=" ", $db=" ")
	{
	
		if ($usuario != "") $this->usuario = $usuario;
		if ($password != "") $this->password = $password;
		if ($db != "") $this->db = $db;
		switch ($this->basedatos)
		{
			case 'MySQL':
				$this->id = mysql_connect("mysql.icesi.edu.co", $this->usuario, $this->password);
				mysql_select_db($this->db, $this->id); 
			break;
			case 'oracle':
				$this->id = OCILogon($this->usuario,$this->password,$this->db);
			break;
		}
	}
	
	
	
	
	/**
	*@method  Toma los datos del archivo de configuracion, donde se encuentran la informacion para la conexion a  la BD y 
	*se los asigna a las variables globales $servidor,$usuario,$password y $db.
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@see     OCILogon($this->usuario,$this->password,$this->db) Funcion nativa de ORACLE
	*@param   $p_file archivo encargado de almacenar los datos de conexion a la BD
	*@return  
	*/
	public function leerarchivo($p_file)
	{
		$this->file = 'material_bibliografico/lib/.config';
		$p_file = $this->file;
		$this->usuario_clave=file($p_file); // File devuelve el contenido del fichero en un array con salto de linea incluido por 
		$this->usuario = substr($this->usuario_clave[0],0,strlen($this->usuario_clave[0]) - 2);
		$this->password = substr($this->usuario_clave[1],0,strlen($this->usuario_clave[1]) - 2);
		$this->db1 = substr($this->usuario_clave[2],0,strlen($this->usuario_clave[2])-2);
		$this->sid = substr($this->usuario_clave[3],0,strlen($this->usuario_clave[3]));
		$this->db = "(DESCRIPTION =
									 (ADDRESS =
										 (PROTOCOL = TCP)
										 (HOST = $this->sid)
										 (PORT = 1521)
									 )
									 (CONNECT_DATA = (SID = $this->db1))
								 )";	
	}
	

	
	/**
	*@method  Función consulta(p_cadena="ninguna"):
	*         Recibe una cadena sql como parámetro, realiza la consulta y el conjunto de
	*         datos resultante lo guarda en la variable global $resultado ,
	*         después extrae todas las filas del conjunto de datos
	*         resultates ($resultado).La función devuelve VERDADERO si
	*         la consulta devuleve al menos 1 fila y FALSO en caso contrario.
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   $p_cadena="ninguna" consulta sql a ser procesada
	*@return  true o false
	*/
	function consulta($p_cadena="ninguna")
	{
	
		$this->ultima_consulta=$p_cadena;
		
		switch ($this->basedatos)
		{
		    case 'MySQL':
			
			$this->resultado=mysql_query($p_cadena,$this->id) or die (mysql_error());
			
			if ( strstr($p_cadena,'SELECT') ) 
			{
				/**
				*bogomez – Blanca Gómez Muñoz
				*2009-11-17
				*si la consulta es de tipo select hace las siguientes ordenes
				*/
		    $this->numcols=mysql_num_fields($this->resultado);
				$this->numfilas=mysql_num_rows($this->resultado);
				
				for ( $n=1;$n<=$this->numfilas;$n++ ) 
				{
					$row=mysql_fetch_row($this->resultado);
				
					for ( $x=1;$x<=mysql_num_fields($this->resultado);$x++ ) 
					{
					  $this->nomcols[$x]=mysql_field_name($this->resultado,$x-1);
						echo "<br>para tipocols".$this->tipocols[$x]=mysql_field_type($this->resultado,$x-1);
						echo "<br>para tamcols".$this->tamcols[$x]=mysql_field_len($this->resultado,$x-1);
						$this->filas[$this->nomcols[$x]][$n]=$row[$x-1];					
					} // Fin for x<= mysql_num_fields
					
				} // Fin for $n<=$this->numfilas
				
			} // Fin if StrStr('SELECT') si la consulta es de tipo select
			
			break;
		
		
		case 'oracle':
			
		$this->resultado=OCIParse($this->id,$p_cadena);
		
		/**
		*bogomez – Blanca Gómez Muñoz
		*2009-11-17
		*A OCIParse se le pasa como parametro $id que es el identificador de conexión y $p_cadena que es la sentecia SQL.
		*Compruebo si existe algun error en la consulta y lo saco por pantalla.
		*/
		if ( !$this->resultado ) 
		{
			$error = OCIError($this->resultado);
			echo $error['messsage'].'<br>';
			exit;
		}
		
		OCIExecute($this->resultado,OCI_COMMIT_ON_SUCCESS);
		
		$this->numcols=OCINumCols($this->resultado);
		$this->numfilas=OCIRowCount($this->resultado);
		
		/**
		*bogomez – Blanca Gómez Muñoz
		*2009-11-17
		*Solo si se trata de un tipo de setencia "SELECT " es cuando extraemos todas las filas a $fila
		*Esto se controla con OCIStatementType que devuelve un string que es ( SELECT | INSERT | DELETE ...etc )
		*/
		if ( OCIStatementType($this->resultado)=='SELECT' ) 
		{
		
		    for ( $n=1;$n<=$this->numcols;$n++ ) 
			{
				$this->nomcols[$n]=OCIColumnName($this->resultado,$n);
				$this->tipocols[$n]=OCIColumnType($this->resultado,$n);
				$this->tamcols[$n]=OCIColumnSize($this->resultado,$n);
			}
			
			$this->numfilas=OCIFetchStatement($this->resultado,$this->filas);
			if ( $this->numfilas > 0 ) { return true; }else{ return false;}
		
		}
		//fin de if OCIStatement == 'SELECT' (Si el tipo de sentencia SQL es una SELECT).
		
		break; //fin de case:'oracle'
		
		} //fin de switch $basedatos
		
	}#fin de funcion consulta
	
	
	
	/**
	*@method  devuelve el número de filas afectadas, por ej_ en sentencias de actualización_
	*         !Esta función no indicará el número de de filas que devuelve una sentencia SELECT!
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   $result consulta sql (update,delete) a ser procesada
	*@return  
	*/
	function numeroRow($result)
	{
		$this->numcols=OCIRowCount($result);	
	}
	
	
	
	/**
	*@method  Esta funcíon le pasas una consulta sql y saca por pantalla una tabla con los resultados ,
	*         si no le pasas nada , lo hace basandose e nla última consulta realizada.
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   $p_sql="ninguna"
	*@return  $this->filas 
	*/
	function ver($p_sql="ninguna")
	{
	
		$border=1;
		$cellspacing=0;
		$cellpading=10;		
		
		if ($p_sql!="ninguna")
		{ 
			$this->consulta($p_sql);			
		}
		
		for ($x=1;$x<=$this->numcols;$x++)
		{
			$this->nomcols[$x];
		}
		echo '<select name="empresa">';
		
		$n=0;
		
		while ($n<=$this->numfilas-1)
		{		
			for ($x=1;$x<=$this->numcols;$x++)
			{			
				echo '<option value="$this->nomcols[$x]">'.$this->filas[$this->nomcols[$x]][$n].'</option>';
			}		
			$n++;
		}
		
	   echo'</select>';
	  
	   return $this->filas;
	  
	}#fin de funcion ver()
	
	
	
	/**
	*@method  Permite obener el id de la conexion
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   
	*@return  $this->id identificador de la conexión
	*/
	function idcone()
	{
		return $this->id;
	}
	
	/**
	*@method  analiza la query usando conn_ Devuelve el identificador de la sentencia si la consulta es válida,
	*         y falso si no lo es_ La query puede ser cualquier sentencia SQL válida
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   
	*@return  $this->s
	*/
	function procesa($idc, $consult)
	{
		$idc=$this->id;
		$this->s = OCIParse($idc, $consult);		
		return $this->s;
	}
	
	/**
	*@method  Busca la siguiente fila (para sentencias SELECT) dentro del result_buffer interno
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   
	*@return  $this->row
	*/
	function numfect($sct)
	{
		$sct=$this->s;
		$this->row = OCIFetch($sct);		
		return $this->row;
	}
	
	/**
	*@method  devuelve el valor de la columna $campo de la fila actual OCIResult() devolverá todo como una cadena
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   
	*@return  $this->dat
	*/
	function datos($ct, $campo)
	{
		$ct = $this->s;
		$this->dat = ociresult($ct, $campo);		
		return $this->dat;
	}
	
	
	/**
	*@method  devuelve el valor de la columna $campo de la fila actual OCIResult() devolverá todo como una cadena
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   
	*@return  $this->dat
	*/
	function ver2($p_sql="ninguna")
	{	
		$border=1;
		$cellspacing = 0;
		$cellpading = 10;		
		
		if ($p_sql!= "ninguna")
		{ 
			$this->consulta($p_sql);		
		}
		
		for ($x = 1;$x<=$this->numcols;$x++)
		{
			$this->nomcols[$x];
		}
				
		$n=0;
		
		while ($n<=$this->numfilas-1)
		{		
			for ($x = 1;$x<=$this->numcols;$x++)
			{			
				echo "<br>x".$x.$contenido[$x][$n]=$this->filas[$this->nomcols[$x]][$n];		
			}	
	   $n++;
		}
	
	return $contenido;	
	}//fin
	
	
	/**
	*@method  devuelve el número de filas afectadas
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   
	*@return  $this->numfilas
	*/
	function filitas()
	{
		return $this->numfilas;
	}
	
	
	/**
	*@method  devuelve el número de columnas en una sentencia
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   
	*@return  $this->numcols
	*/
	function columnas()
	{
		return $this->numcols;
	}
	
	
	/**
	*@method  datoscampos($p_sql="ninguna") despliegue una lista de campos como resultado de SQL procesado
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   $p_sql="ninguna" sentencia sql
	*@return  $this->sl
	*/
	function datoscampos($p_sql="ninguna")
	{	
		$this->sl=ociparse($this->id,$p_sql);//procesando la consulta
		oci_execute($this->sl, OCI_DEFAULT);//ejecuntando la consulta
		?>
		 <select name="empresas">
		 <?php
		while (OCIFetch($this->sl))
		{?>
		
			<option name="<?php  echo $ids=ociresult($this->sl, "CODIGO");?>"><?php
			echo $this->contcp=trim(ociresult($this->sl,"NOMBRE"),"%").(" ".trim($this->contcp=ociresult($this->sl,"NOMBRE_CORTO"),"%")); ?></option>
			<?php
		}//?>
		</select>
		<?php
		
		return $this->sl;
	
	}#fin datoscampos
	
	
	/**
	*@method  datoscampos($p_sql="ninguna") despliegue una lista de campos como resultado de SQL procesado
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   $p_sql="ninguna" sentencia sql
	*@return  $this->sl
	*/
	function idconsult($orac_sql="ninguna")
	{	
	$this->sl=ociparse($this->id,$orac_sql);//procesando la consulta
	$ejcut=oci_execute($this->sl, OCI_DEFAULT);//ejecuntando la consulta	
	return $this->sl;
	}//
	
	/**
	*@method  Confirma todas las sentencias pendientes para la conexión con Oracle
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   
	*@return  
	*/
	function commit()
	{	
		switch ($this->basedatos) 
		{
			case 'MySQL':
				echo 'funcion comit no soportada';
			break;
			case 'oracle':
				OCICommit($this->id);
			break;
		} #fin switch
	
	}#Fin de la funcion
	
	/**
	*@method  restablece todas las transacciones sin confirmar para la conexión Oracle
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   
	*@return  
	*/
	function rollback()
	{
		switch ($this->basedatos) 
		{		
			case 'MySQL':
				echo 'funcion rollback no soportada';
			break;			
			case 'oracle':
				OCIRollback($this->id);
			break;
		
		}#fin switch
	}#fin de funcion
	
	
	
	/**
	*@method  cierra una conexión con Oracle
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
	*@param   
	*@return  
	*/
	function cerrar()
	{
		switch ($this->basedatos)
		{
			case 'MySQL':
			mysql_close($this->id);
			break;
			case 'oracle':
			OCILogOff($this->id);
			break;
		}	
	}#fin de la función cerrar
	
	
	
	/**
    *@method  Construye un DELETE dada una tabla de la BD y el numero de columna
	*@autor   bogomez - Blanca Gómez Muñoz
	*@since   2008-08-19
    *@param   
    *@return  $sql consulta formada
    */
	function borrar_fila($p_tabla,$p_numero)
	{	
		$sql='DELETE FROM '.$p_tabla;		
		$sql.=' WHERE ';
		
		for ($n=1;$n<$this->numcols;$n++)
		{
			if ( ($this->tipocols[$n]=='string') or ($this->tipocols[$n]=='blob') ) 
			{
				$sql.=$this->nomcols[$n].'="'.$this->filas[$this->nomcols[$n]][$p_numero].'" AND ';
			}
			else
			{
				$sql.=$this->nomcols[$n].'='.$this->filas[$this->nomcols[$n]][$p_numero].' AND ';
			}
		
		} #fin_for		
		$sql= substr ($sql, 0, -4);		
		return $sql;	
	}	
}#fin de class	
?> 