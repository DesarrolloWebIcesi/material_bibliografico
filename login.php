<?php
      if (basename($_SERVER['PHP_SELF']) != "index.php"){
        header("Location: index.php");
        die;
      }
	  extract($_POST);
?>

<div id="form_login">
	<form method="post" action="<?php echo getenv('REQUEST_URI'); ?>" name="login" onsubmit="return validarLogin();" style="margin:0px;"> 
	  <table align="center" cellpadding="4" cellspacing="0">
	    <tr>
		  <th colspan="2" bgcolor="#CCCCCC" style="border: solid 1px black;">
		    Por favor ingrese su nombre de usuario y su contrase&ntilde;a
		  </th>
		</tr>
		<tr>
		  <td align="right" style="border-left:solid 1px black;">Nombre de usuario</td>
		  <td style="border-right:solid 1px black;"><input type="text" name="usuario" value="<?php echo $usuario; ?>" /></td>
		</tr>
		<tr>
		  <td align="right" style="border-left:solid 1px black;">Contrase&ntilde;a</td>
		  <td style="border-right:solid 1px black;"><input type="password" name="password" /></td>
		</tr>
	    <tr>
		  <td colspan="2" align="center" style="border-right:solid 1px black; border-bottom:solid 1px black; border-left:solid 1px black;">
	        <input type="submit" name="boton" value="Ingresar"/>
		  </td>
		</tr>
	  </table>
	</form>
</div>