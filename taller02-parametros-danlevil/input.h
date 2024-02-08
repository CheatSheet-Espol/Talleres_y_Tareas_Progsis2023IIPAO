#ifndef INPUT_H
#define INPUT_H

/**
 * Función get_from_console muestra una forma segura de ingresar una linea de texto desde consola.
 * IMPORTANTE: line debe ser liberado con free() después de su uso.
 *
 * @param line Cadena de carecteres a ser llenada por getline. Este parametro será llenado con
 *             toda la línea de texto ingresada sin incluir el salto de línea '\n'.
 *
 * @return Número de caracteres en la línea de texto, no considera '\n'. -1 si hubo error.
 */
int get_from_console(char **line);

#endif /* INPUT_H */