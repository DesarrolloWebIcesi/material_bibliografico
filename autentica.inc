<?php

include_once('Mantis.inc');

class autentica {

    function autenticarUsuario($nombreUsuario, $clave) {
        $servidor_ldap = "ldap://iden.icesi.edu.co/";
        $ds = ldap_connect($servidor_ldap);
        if (!$ds) {
            return 3;
        }

        if (!ldap_set_option($ds, LDAP_OPT_PROTOCOL_VERSION, 3)) {
            return 3;
        }

        //Primero se intenta hacer bind para empleados y profesores tiempo completo
        $dnUsuario = "cn=" . $nombreUsuario . ",cn=colaboradores,cn=users,dc=icesi,dc=edu,dc=co";
        //$dnUsuario = "cn=".$nombreUsuario.",cn=busqueda,cn=dsistemas,cn=users,dc=icesi,dc=edu,dc=co";
        $bind = @ldap_bind($ds, $dnUsuario, $clave);
        //Si no está, se intenta para hora cátedra
        if (!$bind) {
            echo "no esta, buscando si es hora catedra.<br/>";
            $dnUsuario = "cn=" . $nombreUsuario . ",cn=profesores,cn=users,dc=icesi,dc=edu,dc=co";
            $bind = @ldap_bind($ds, $dnUsuario, $clave);
            //Si no está, se intenta para los empleados temporales
            if (!$bind) {
                echo "no esta, buscando si es temporal.<br/>";
                $dnUsuario = "cn=" . $nombreUsuario . ",cn=temporales,cn=users,dc=icesi,dc=edu,dc=co";
                $bind = @ldap_bind($ds, $dnUsuario, $clave);
            }
        }

        //Lo siguiente muestra todos los datos almacenados en el LDAP del usuario buscado
        $resultado = @ldap_search($ds, "cn=$log,cn=colaboradores,cn=users,dc=icesi,dc=edu,dc=co", "cn=*");
        $datos = @ldap_get_entries($ds, $resultado);
        for ($i = 0; $i <= $datos["count"]; $i++) {
            for ($j = 0; $j <= $datos[$i]["count"]; $j++) {
                echo $datos[$i][$j] . ": " . $datos[$i][$datos[$i][$j]][0] . "<br/>";
            }
        }

        if ($bind && !empty($clave)) {
            /* Lo siguiente valida si el usuario es profesor hora cátedra o si es tiempo completo
              $dnHoraCatedra = "cn=profesor_a,cn=de_simbiosis,cn=GruposAcademico,cn=portal.080624.114943.307223000,cn=groups,dc=icesi,dc=edu,dc=co";
              $dnTiempoCompleto = "cn=profesor,cn=de_simbiosis,cn=gruposadministrativo,cn=portal.080624.114943.307223000,cn=groups,dc=icesi,dc=edu,dc=co";

              $esHoraCatedra = @ldap_compare($ds, $dnHoraCatedra, "uniqueMember", $dnUsuario);
              $esTiempoCompleto = @ldap_compare($ds, $dnTiempoCompleto, "uniqueMember", $dnUsuario);

              if ($esHoraCatedra || $esTiempoCompleto){
              $resultado =@ldap_search($ds, $dnUsuario, "cn=*");
              $datos = @ldap_get_entries($ds, $resultado);

              $_SESSION['idUsuario'] = $datos[0]["cn"][0];
              $_SESSION['nombresUsuario'] = $datos[0]["givenname"][0];
              $_SESSION['apellidosUsuario'] = $datos[0]["sn"][0];
              $_SESSION['correoUsuario'] = $datos[0]["mail"][0];
              return 0;
              }
              return 1; */
            echo "se encontró en lDAP";
            $valorRetorno = 0;

            /* Se verifica que el usuario está registrado en la Base de Datos de Mantis, para que 
             * al guardar la solicitud, este quede como el "Informador" del caso */
            $mantis = new Mantis();
            $idInformadorMantis = $mantis->obtenerIdUsuarioMantis($nombreUsuario);

            if (is_null($idInformadorMantis)) {
                $valorRetorno = 1;
                //echo "no se encontró en mantis";
            } else {
                $resultado = @ldap_search($ds, $dnUsuario, "cn=*");
                $datos = @ldap_get_entries($ds, $resultado);

                $_SESSION['idUsuario'] = $datos[0]["cn"][0];
                $_SESSION['nombresUsuario'] = $datos[0]["givenname"][0];
                //$_SESSION['nombresUsuario'] = 'Nombre';
                $_SESSION['apellidosUsuario'] = $datos[0]["sn"][0];
                //$_SESSION['apellidosUsuario'] = 'Completo';
                $_SESSION['correoUsuario'] = $datos[0]["mail"][0];
                //$_SESSION['correoUsuario'] = 'correo@icesi.edu.co';
                $valorRetorno = 0;
            }
        } else {
            echo "no se encontró en LDAP";
            $valorRetorno = 2;
        }

        ldap_unbind($ds);
        return $valorRetorno;
    }

}

?>