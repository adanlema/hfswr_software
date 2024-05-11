# Procedimiento para crear un archivo .service
Tenemos que ir a la carpeta:
- cd /etc/systemd/system

Podemos ver los permisos de cada servicio usando el comando: *ls -l*
### Primero copiamos el archivo server redpiraya_scpi.service
- cp redpiraya_scpi.service transmisor.service

### Deshabilite los servicios que imponia red pitaya
- sudo systemctl disable redpitaya_nginx.service

Tambien deberiamos desactivar redpitaya_scpi.service y redpitaya_startup.service, pero estos ya estaban deshabilitados desde antes. Ademas si queremos ver el estatus de los servicios podemos poner:

- service NOMBREDELSERVICIO status (no se coloca el .service)

Luego use **reboot** para reiniciar los procesos. Antes me aparecia un error porque no podia conectar el socket del servidor, eso era porque todavia no se le habia asignado una IP al socket, entonces no podia entrar. Para resolver esto se coloco de IP el "0.0.0.0" de esta manera escuchaba mi placa cualquier IP pero solo iba a tener en cuenta el puerto colocado (PORT:5566).

Luego comensamos a editar el archivo **transmisor.service**. Comenzamos editando **Description=** colocando una descripcion acorde al trabajo. Luego cambiamos lo siguiente:
- ExecStartPre=/bin/sh -c "cat /root/tx_wrapper.bit > /dev/xdevcfg"
- ExecStart=/root/transmisor/build/bin/app.elf

De esta manera, lo que hacias que antes de realizar el **start** del servicio cargue el bitstream y luego ejecute el archivo **app.elf**. 

Cuando fallo el servicio del transmisor no podiamos saber en donde, para ello usamos el comando:
- journalctl -u transmisor.service

Este mismo nos permite ver la consola como va comenzado el servicio y nos muestra los mensajes de **perror**, los cuales son muy importantes ya que nos permite ver donde fallo. Ahi fue donde nos dimos cuenta que no se creaba el socket porque me salia el error puesto: *Error al vincular el socket: Cannot assign requested address*. 

Para ver los archivos ejecutandose (app.elf), usamos el comando:
- ps -aux

Luego para ver los log, podemos entrar a la carpeta *cd /var/log*.