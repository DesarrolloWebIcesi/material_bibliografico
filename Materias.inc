<?php
//Esta clase contiene las funciones referentes a los campos Materias, usados por los formularios de adquisición de material bibliográfico de la Biblioteca
class Materias{
  /*******************************************************************************
   Nombre:     adicionarCamposMaterias
   Propósito:  Genera el HTML para incluir las filas y el valor de cada celda de las materias que el usuario haya agregado la última vez que envió el formulario.
               Si es la primera vez que el usuario va a diligenciar el formulario se debe pasar como valor de cantidadCampos 1.
   Entradas:   - cantidadCampos : indica cuantas filas con campos para las materias se van a generar.
                                  Si es la primera vez que el usuario va a diligenciar el formulario se debe pasar como valor de cantidadCampos 1.
               - camposError    : es un arreglo que contiene los errores, si los hay, en cada campo respectivo.
			                      Por ejemplo, la posición con clave nombreMateria1 contiene el error del campo nombreMateria1 y así sucesivamente.
   Salida:     - Código HTML para marcar que al menos un campo de las materias tiene un valor indebido o está vacío
               - Código HTML para las filas y el valor de cada celda de la tabla de materias del formulario
   
   Revisiones:
   Ver        Fecha       Autor            Descripción
   ---------  ----------  ---------------  ------------------------------------
   1.0        19-ago-09   gavarela         Creación

   Notas:
         El código para que muestre el error de cada campo debajo de este se ha comentado ya que ello deja la tabla muy poco estética, pero se deja por si se desea implementar algo similar.
  ********************************************************************************/
  function adicionarCamposMaterias($cantidadCampos, $camposError){
	$sinErrores = true;
	for($contadorCampos = 1; $contadorCampos <= $cantidadCampos; $contadorCampos++){
	  echo "<tr>";
	  
      echo "<td><input name='nombreMateria".$contadorCampos."' id='nombreMateria".$contadorCampos."' type='text' size='17' maxlength='80' value='".$_POST['nombreMateria'.$contadorCampos]."'/>";
	  /*Esto pone los mensajes de error debajo de cada campo, pero se deja en comentario, ya que esto deforma la tabla del formulario
	  if (isset($camposError['nombreMateria'.$contadorCampos]))
	    echo "<br/><div class='error'>".$camposError['nombreMateria'.$contadorCampos]."</div>";*/
	  echo "</td>";
	  $sinErrores = $sinErrores && !isset($camposError['nombreMateria'.$contadorCampos]);
	  
	  echo "<td><input name='codigoMateria".$contadorCampos."' id='codigoMateria".$contadorCampos."' type='text' size='5' maxlength='5' value='".$_POST['codigoMateria'.$contadorCampos]."'/>";
	  /*Esto pone los mensajes de error debajo de cada campo, pero se deja en comentario, ya que esto deforma la tabla del formulario
	  if (isset($camposError['codigoMateria'.$contadorCampos]))
	    echo "<br/><div class='error'>".$camposError['codigoMateria'.$contadorCampos]."</div>";*/
	  echo "</td>";
	  $sinErrores = $sinErrores && !isset($camposError['codigoMateria'.$contadorCampos]);
      
	  echo "<td><input name='departamentoMateria".$contadorCampos."' id='departamentoMateria".$contadorCampos."' type='text' size='17' maxlength='60' value='".$_POST['departamentoMateria'.$contadorCampos]."'/>";
	  /*Esto pone los mensajes de error debajo de cada campo, pero se deja en comentario, ya que esto deforma la tabla del formulario
	  if (isset($camposError['departamentoMateria'.$contadorCampos]))
	    echo "<br/><div class='error'>".$camposError['departamentoMateria'.$contadorCampos]."</div>";*/
	  echo "</td>";
	  $sinErrores = $sinErrores && !isset($camposError['departamentoMateria'.$contadorCampos]);
	  
      echo "</tr>";
	}
	
	if(!$sinErrores){
	  return "<div class='error'>Complete correctamente todos los campos</div>";
	}else{
	  return "";
	}
  }
}