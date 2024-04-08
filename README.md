# Transmisor y Receptor de un Radar de Onda Superficial usando un SDR

**Autores: Carcamo, Mariano Gabriel - Lema, Adan Juan Angel**

El proyecto implica la implementación de un Radar de Onda Superficial utilizando *SDR* (Radio Definida por Software), diseñado específicamente para aplicaciones de RF (Radio Frecuencia). En este repositorio, se encuentran los módulos de la FPGA implementados tanto para el transmisor como para el receptor. Además, se incluyen los códigos necesarios para cargar en el PS correspondiente.

## Subir el bitstream a la FPGA
- **TERMINAL1** (CONECTAR CON LA PLACA)
    - ssh root@rp-xxxxxx.local
    - CLAVE: root
    - redpitaya > rw

- **TERMINAL2** (SUBIR ARCHIVO.BIT A LA PLACA)
    - scp ARCHIVO.bit root@rp-xxxxxx.local:/root
    - CLAVE: root
- **TERMINAL1** 
    - redpitaya > ls
    - redpitaya > cat ARCHIVO.bit > /dev/xdevcfg

## Subir el codigo del PS a la FPGA
El proceso es similar al de cargar el bitstream, excepto que en este caso debemos transferir la carpeta deseada (**transmisor/receptor**)a la FPGA. Para transferir la carpeta se debe usar el comando:

**scp -r CARPETA root@rp-xxxxxx.local:/root**

Una vez que la carpeta se haya transferido con éxito, es necesario ingresar a ella y ejecutar el comando **make** para compilar, luego para ejecutar el código usamos el comando **make run**.

## Tabla de comandos

| Comando | Descripcion |
| --- | --- |
| make | Compila el codigo |
| make clean | Borra la carpeta *build* |
| make run | Ejecutar el programa |