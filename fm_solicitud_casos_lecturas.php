<?php
/**
 *
 * @since 2013-01-25 damanzano se cometaron algunas líneas donde se usaban variables no definidas y generaban errores en el servidor.
 */
      if (!$_SESSION['idUsuario']){
	    header("Location: index.php");
		die;
	  }
	  extract($_POST);
	  
	  include_once("Adquisiciones.inc");
	  $adquisiciones = new Adquisiciones();
	  $departamentos = $adquisiciones->obtenerDepartamentosAcademicos();
	  //Se quita el N/A, ya que para este caso ese valor no debe permitirse
	  array_splice($departamentos, array_search('N/A', $departamentos), 1);
	  sort($departamentos);
	  
	  $programas = $adquisiciones->obtenerProgramasAcademicos();
	  sort($programas);
?>
    
<div id="form_solic_caso_lectura">
    <p>
	  Para hacer su solicitud, por favor ingrese los datos solicitados en el siguiente formulario.<br/>
	  Los campos que est&aacute;n en <b>negrilla</b> y con asterisco (*) al final son obligatorios.
	</p>
	<!-- Se usa la función javascript validarFormularioCasoLectura para no tener que poner una comparación de cada campo en el onSubmit -->
	<form action="<?php echo getenv('REQUEST_URI'); ?>" name="formulario" method="post" onsubmit="return validarFormularioCasoLectura();">
	  <table border="1" align="center" cellpadding="4" cellspacing="0">
        <tr bgcolor="#CCCCCC">
          <td colspan="2"><b>Formulario de solicitud de casos o lecturas</b></td>
        </tr>
		
		<tr>
		  <td class="obligatorio">Profesor que solicita el caso/lectura*</td>
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
		  <td class="opcional">C&oacute;digo de la publicaci&oacute;n</td>
		  <td><input name="codigo" id="codigo" type="text" size="50" maxlength="100" value="<?php echo $codigo?>"/></td>
        </tr>
		<tr>
          <td class="obligatorio">Autor principal*</td>
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
          <td class="obligatorio">Publicador*</td>
          <td>
		    <input name="publicador" id="publicador" type="text" size="50" maxlength="700" value="<?php echo $publicador?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['publicador']))
			    echo "<br/><div class='error'>".$camposError['publicador']."</div>";
			?>
		  </td>
        </tr>
		<tr>
          <td class="opcional">A&ntilde;o de publicaci&oacute;n</td>
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
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
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
          <td class="obligatorio">Cenco*</td>
          <td>
		    <input name="cenco" id="cenco" type="text" size="50" maxlength="700" value="<?php echo $cenco?>"/>
			<!-- Si existe un arreglo $camposError y tiene un valor asignado con el nombre del campo es porque el formulario fue validado y se encontró un error en el valor del campo -->
			<?php
			  if (isset($camposError['cenco']))
			    echo "<br/><div class='error'>".$camposError['cenco']."</div>";
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
		<input type="hidden" name="tipo" id="tipo" value="caso_lectura" />
		<input type="hidden" name="tipoSolicitud" id="tipoSolicitud" value="Casos o lecturas" />
		&nbsp;
		<input type="reset" name="limpiar" id="limpiar" value="Limpiar" />
	  </p>
	</form>
</div>