### Comandos para poder realizar la conexion con los servidores

Para conectarnos con el server de las placas utilizamos un tunel SSH, se utilizo esto para aumentar la seguridad de la conexion. Se utilizo los siguientes comandos:
* ssh -N -f -L PORT_LOCAL:IP_PLACA:PORT_PLACA root@rp-XXXXXX.local

Donde **PORT_LOCAL** es un puerto de nuestra PC, **IP_PLACA** es la direccion IP base de la redpitaya y **PORT_PLACA** es el puerto de la redpitaya que nos queremos conectar. Este comando nos pedira la contraseña de la conexion **ssh** para poder acceder al tunel.

Una vez conectados podemos ejecutar nuestra aplicacion en la PC. Para ello recurrimos al comando **make run** para ejecutar el archivo **.elf**, en caso de que no este creado se debe ejecutar **make** antes del comando mencionado. De esta manera, se ejecuta el programa que nos permite modificar los parametros del transmisor y de los receptores.

### Cerrar conexion SSH y tunel SSH
para poder cerrar la conexion **ssh** tenemos que seguir los siguientes pasos.
* ps -C ssh

Este comando nos muestra las conexiones **ssh** realizadas y nos entrega una **PID** a cada conexion realizada. Una vez terminada la aplicacion ejecutada tenemos que cerrar las conexiones ssh, para ello ejecutamos el siguiente comando:
* kill PID

