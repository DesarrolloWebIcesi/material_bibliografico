<?php
/**
 *
 * @since 2013-01-25 damanzano se cometaron algunas líneas donde se usaban variables no definidas y generaban errores en el servidor.
 */
//ini_set('display_errors',1); 
//error_reporting(E_ALL);
    if (!$_SESSION['idUsuario']){
	    header("Location: index.php");
		die;
	  }
	  extract($_POST);
	  //Si cantidadMaterias está en la sesión, el usuario ya envió al menos una vez el formulario.
	  //Este valor se usa para volver a generar el número de filas de los detalles de materias que el usuario generó la vez anterior
	  if(isset($_SESSION['cantidadMaterias'])){
        $cantidadMaterias = $_SESSION['cantidadMaterias'];
      }else{
        $cantidadMaterias = 1;
      }
  	  
	  //Esta validación se hace ya que no se puede hacer este include cuando el usuario ya envió este formulario
	  if(!class_exists('Materias')) {
	    include "Materias.inc";
	  }
	  $materias = new Materias();
	  
	  include_once("Adquisiciones.inc");
	  $adquisiciones = new Adquisiciones();
	  $departamentos = $adquisiciones->obtenerDepartamentosAcademicos();
	  //Se quita el N/A, ya que para este caso ese valor no debe permitirse
	  array_splice($departamentos, array_search('N/A', $departamentos), 1);
	  sort($departamentos);
	  
	  $programas = $adquisiciones->obtenerProgramasAcademicos();
	  sort($programas);
?>

<div id="form_solic_libro">
    <p>
	  Para hacer su solicitud, por favor ingrese los datos solicitados en el siguiente formulario.<br/>
	  Los campos que est&aacute;n en <b>negrilla</b> y con asterisco (*) al final son obligatorios.
	</p>
	<!-- Se usa la función javascript validarFormularioLibro para no tener que poner una comparación de cada campo en el onSubmit -->
	<form action="<?php echo getenv('REQUEST_URI'); ?>" name="formulario" method="post" onsubmit="return validarFormularioLibro();">
	  <table border="1" align="center" cellpadding="4" cellspacing="0">
        <tr bgcolor="#CCCCCC">
          <td colspan="2"><b>Formulario de solicitud de libros</b></td>
        </tr>
        
		<tr>
		  <td class="obligatorio">Profesor que solicita el libro*</td>
          <td>
		    <input name="profesor" id="profesor" type="text" size="50" maxlength="700" value="<?php echo $profesor?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['profesor']))
			    echo "<br/><div class='error'>".$camposError['profesor']."</div>";
			?>
		  </td>
		 </tr>
		 <tr>
		  <td class="obligatorio">Correo profesor*</td>
          <td>
		    <input name="correo_profesor" id="correo_profesor" type="text" size="50" maxlength="700" value="<?php echo $correo_profesor?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['correo_profesor']))
			    echo "<br/><div class='error'>".$camposError['correo_profesor']."</div>";
			?>
		  </td>
		 </tr>
		 <tr>
		  <td class="opcional">Tel&eacute;fono Profesor</td>
          <td>
		    <input name="tel_profesor" id="tel_profesor" type="text" size="50" maxlength="700" value="<?php echo $tel_profesor?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['tel_profesor']))
			    echo "<br/><div class='error'>".$camposError['tel_profesor']."</div>";
			?>
		  </td>
		 </tr>
		 <tr>
          <td class="obligatorio">T&iacute;tulo*</td>
          <td>
		    <input name="titulo" id="titulo" type="text" size="50" maxlength="700" value="<?php echo $titulo?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['titulo']))
			    echo "<br/><div class='error'>".$camposError['titulo']."</div>";
			?>
		  </td>
        </tr>
		 <tr>
          <td class="obligatorio">Autor*</td>
          <td>
		    <input name="autor" id="autor" type="text" size="50" maxlength="700" value="<?php echo $autor?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['autor']))
			    echo "<br/><div class='error'>".$camposError['autor']."</div>";
			?>
		  </td>
        </tr>
		<tr>
          <td class="opcional">ISBN<br/><div class="isxn">Sin guiones ni espacios</div></td>
          <td>
		    <input name="isbn" id="isbn" type="text" size="13" maxlength="13" value="<?php echo $isbn?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['isbn']))
			    echo "<br/><div class='error'>".$camposError['isbn']."</div>";
			?>
		  </td>
        </tr>
		<tr>
          <td class="obligatorio">Editorial*</td>
          <td>
		    <input name="editorial" id="editorial" type="text" size="50" maxlength="700" value="<?php echo $editorial?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['editorial']))
			    echo "<br/><div class='error'>".$camposError['editorial']."</div>";
			?>
		  </td>
        </tr>		
		<tr>
          <td class="obligatorio">A&ntilde;o de publicaci&oacute;n*</td>
          <td>
		    <input name="fechaPublicacion" id="fechaPublicacion" type="text" size="4" maxlength="4" value="<?php echo $fechaPublicacion?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['fechaPublicacion']))
			    echo "<br/><div class='error'>".$camposError['fechaPublicacion']."</div>";
			?>
		  </td>
        </tr>
		<tr>
          <td class="opcional">Edici&oacute;n</td>
          <td>
		    <input name="edicion" id="edicion" type="text" size="50" maxlength="700" value="<?php echo $edicion?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['edicion']))
			    echo "<br/><div class='error'>".$camposError['edicion']."</div>";
			?>
		  </td>
        </tr>
		<tr>
          <td class="obligatorio">Temas*</td>
          <td>
		    <textarea name="temas" id="temas" cols="39" rows="3" ><?php echo $temas?></textarea>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['temas']))
			    echo "<br/><div class='error'>".$camposError['temas']."</div>";
			?>
		  </td>
        </tr>
		<tr>
          <td class="obligatorio" align="center">Materia(s)<br /> 
          en que se usar&aacute;*</td>
          <td>
            <!-- Los campos para la información de las materias se ponen en una tabla dentro de esta celda para que quede mejor organizada y se distinga una materia de otra -->
			<table id="tablaMaterias">
			  <tbody>
                <tr align="center">
                  <th>Nombre*</th>
                  <td>C&oacute;digo</td>
                  <td>Departamento</td>
                </tr>
                <!-- La función PHP adicionarCamposMaterias muestra el número de filas que el usuario generó la última vez que envió el formulario, si es la primera vez genera una fila.
				Tiene la opción de verificar si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo, pero esto está comentado ya que incluir esto al lado del campo daña la visual de la tabla interna-->
				<?php $mensajeErrorMaterias = $materias->adicionarCamposMaterias($cantidadMaterias, $camposError); ?>
				<input type="hidden" name="cantidadMaterias" id="cantidadMaterias" value="<?php echo $cantidadMaterias?>" />
			  </tbody>
            </table>
			<!-- Si la variable $mensajeErrorMaterias tiene un valor es porque el formulario fue validado y se encontró un error en al menos un campo.
			No se muestra el error al lado del campo respectivo de la materia dado que eso dañaría la distribución de la tabla interna de materias -->
			<?php
			  if($mensajeErrorMaterias != ""){
                echo $mensajeErrorMaterias;
              }
			?>
			<!-- Este link llama a la función javascript agregarFila la cual adiciona una fila a la tabla de materias del formulario -->
            <div id="enlacesFilas" align="right">
              <a href="javascript:agregarFila('tablaMaterias', 'enlacesFilas')" title="Agregar una materia">Agregar materia</a>
              &nbsp;
			  <?php
			    if ($cantidadMaterias > 1){?>
				  <a id="enlaceElimina" href="javascript:borrarFila('tablaMaterias', 'enlaceElimina')" title="Eliminar la última materia">Eliminar &uacute;ltima materia</a>
		  <?php }
			  ?>
            </div>
			<!-- Si JavaScript no está habilitado en el navegador, se indica que no se podrán agregar materias en esta tabla -->
			<script type="text/javascript">
            </script>
            <noscript>
              <div style="color:#FF0000; font-size:10px">Para agregar m&aacute;s materias debe habilitar JavaScript en su navegador</div>
            </noscript>
          </td>
		</tr>
		<tr>
		  <td class="obligatorio">Departamento al que se <br/>
		  cargar&aacute; la compra*</td>
		  <td>
		    <select name="departamento" id="departamento">
			<option value="" selected>Seleccionar</option>
			<?php 
			foreach ($departamentos as &$nombreDepartamento) {
			  echo '<option value="'.utf8_encode($nombreDepartamento).'">'.utf8_encode($nombreDepartamento).'</option>';	
			  
			  //2012-01-25 damanzano se comentan las siguientes líneas de código pues son innecesarias y hacen uso de variables sin definir, En su lugar se deja solo la línea de arriba
			  /*
			  if ($departamento == $nombreDepartamento){
			    echo '<option value="'.htmlentities($nombreDepartamento).'" selected>'.htmlentities($nombreDepartamento).'</option>';
			  }else{
			    echo '<option value="'.htmlentities($nombreDepartamento).'">'.htmlentities($nombreDepartamento).'</option>';
			  }
			  */
			}
			unset($nombreDepartamento);
			?>
			</select>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontr&oacute; un error en el valor del campo -->
			<?php
			  if (isset($camposError['departamento']))
			    echo "<br/><div class='error'>".$camposError['departamento']."</div>";
			?>
		  </td>
		</tr>
		<tr>
		  <td class="obligatorio">Programa responsable<br/>
		  de la solicitud*</td>
		  <td>
			<select name="programa" id="programa">
			<option value="" selected>Seleccionar</option>
			<option value="n-a">No aplica</option>
			<?php 
			foreach ($programas as &$nombrePrograma) {
			  echo '<option value="'.utf8_encode($nombrePrograma).'">'.utf8_encode($nombrePrograma).'</option>';
			  
			  //2012-01-25 damanzano se comentan las siguientes líneas de código pues son innecesarias y hacen uso de variables sin definir, En su lugar se deja solo la línea de arriba
			  /*
			  if ($programa == $nombrePrograma){
			    echo '<option value="'.htmlentities($nombrePrograma).'" selected>'.htmlentities($nombrePrograma).'</option>';
			  }else{
			    echo '<option value="'.htmlentities($nombrePrograma).'">'.htmlentities($nombrePrograma).'</option>';
			  }
			  */
			}
			unset($nombrePrograma);
			?>
			</select>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['programa']))
			    echo "<br/><div class='error'>".$camposError['programa']."</div>";
			?>
		  </td>
		</tr>
		<tr>
		  <td class="obligatorio">Es un texto gu&iacute;a<br /> 
		  y debe estar en reserva*</td>
		  <td>
		    <input type="radio" name="reserva" id="reserva" value="si" <?php if(isset($reserva)) { if($reserva=="si") echo "checked='checked'"; }else{ echo "checked='checked'"; } ?>  />S&iacute;
		    <br/>
		    <input type="radio" name="reserva" id="reserva" value="no" <?php if($reserva=="no") echo "checked='checked'";?> />No
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['reserva']))
			    echo "<br/><div class='error'>".$camposError['reserva']."</div>";
			?>
		  </td>
		</tr>
		<tr>
		  <td class="obligatorio">Se necesita<br /> 
		  urgentemente*</td>
		  <td>
		    <input type="radio" name="urgente" id="urgente" value="si" <?php if(isset($urgente)) { if($urgente=="si") echo "checked='checked'"; }else{ echo "checked='checked'"; } ?>  />S&iacute;
		    <br/>
		    <input type="radio" name="urgente" id="urgente" value="no" <?php if($urgente=="no") echo "checked='checked'";?> />No
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['urgente']))
			    echo "<br/><div class='error'>".$camposError['urgente']."</div>";
			?>
		  </td>
		</tr>
		<tr>
		  <td class="obligatorio">Cantidad requerida*</td>
		  <td>
		    <input name="cantidad" id="cantidad" type="text" size="2" maxlength="2" value="<?php echo $cantidad?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['cantidad']))
			    echo "<br/><div class='error'>".$camposError['cantidad']."</div>";
			?>
		  </td>
		</tr>
		<tr>
		  <td class="opcional">Distribuidor recomendado</td>
		  <td>
		    <input name="distribuidor" id="distribuidor" type="text" size="50" maxlength="100" value="<?php echo $distribuidor?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['distribuidor']))
			    echo "<br/><div class='error'>".$camposError['distribuidor']."</div>";
			?>
		  </td>
        </tr>
        <tr>
		  <td class="opcional">Comentarios</td>
		  <td>
		    <textarea name="comentarios" id="comentarios" cols="39" rows="3" ><?php echo $comentarios?></textarea>
            <!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['comentarios']))
			    echo "<br/><div class='error'>".$camposError['comentarios']."</div>";
			?>
		  </td>
        </tr>
	  </table>
	  <p align="center">
	    <input type="submit" name="enviar" id="enviar" value="Enviar" />
		<input type="hidden" name="tipo" id="tipo" value="libro" />
		<input type="hidden" name="tipoSolicitud" id="tipoSolicitud" value="Libros" />
		&nbsp;
		<input type="reset" name="limpiar" id="limpiar" value="Limpiar" />
	  </p>
	</form>
    
	<!-- Se usa el valor de $cantidadMaterias para que la función javascript setContadorFilas fije el valor de la variable contadorFilas al cargar la página -->
	<script language="javascript" type="text/javascript">
		setContadorFilas('<?php echo $cantidadMaterias?>');
	</script>
</div>