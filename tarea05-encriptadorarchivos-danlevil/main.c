#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <dirent.h>

#include "blowfish.h"
#include "libsha1.h"

bool dflag = false; // Decrypt/Encrypt flag
bool fflag = false; // Folder flag

void print_help(char *command)
{
    printf("secret encripta o desincripta un archivo o carpeta usando el algoritmo Blowfish.\n");
    printf("uso:\n %s [-d] [-f] -k <key> <nombre_archivo|nombre_carpeta>\n", command);
    printf(" %s -h\n", command);
    printf("Opciones:\n");
    printf(" -h\t\t\tAyuda, muestra este mensaje\n");
    printf(" -d\t\t\tDesencripta el archivo en lugar de encriptarlo.\n");
    printf(" -f\t\t\tEncripta/Desencripta una carpeta en vez de un archivo.\n");
    printf(" -k <key>\t\tEspecífica la clave (key) de encriptación, 8 bytes en hex.\n");
}

void create_directories()
{
    // Crear carpetas encriptadas y desencriptadas si no existen
    mkdir("archivos_encriptados", 0777);
    mkdir("archivos_desencriptados", 0777);
}

void encrypt_decrypt_file(char *input_file, char *key_arg_str)
{
    unsigned char sha1_key[SHA1_DIGEST_SIZE];
    sha1(key_arg_str, strlen(key_arg_str), sha1_key);

    unsigned char key_arg[8];
    for (int i = 0; i < 8; i++)
    {
        key_arg[i] = sha1_key[i];
    }

    char *output_extension = dflag ? ".dec" : ".enc";
    size_t output_len = strlen(input_file) + strlen(output_extension) + 1;
    char *output_file = calloc(output_len, sizeof(char));
    strcpy(output_file, input_file);
    strcat(output_file, output_extension);

    int fd_output;
    if (dflag)
    {
        fd_output = open("archivos_desencriptados", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    }
    else
    {
        fd_output = open("archivos_encriptados", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    }

    unsigned char input_buf[BLOWFISH_BLOCK_SIZE] = {0};
    unsigned char output_buf[BLOWFISH_BLOCK_SIZE] = {0};
    BLOWFISH_KEY key;

    blowfish_key_setup(key_arg, &key, 8);

    int fd_input = open(input_file, O_RDONLY);

    while (read(fd_input, input_buf, sizeof(input_buf)) > 0)
    {
        if (dflag)
        {
            blowfish_decrypt(input_buf, output_buf, &key);
        }
        else
        {
            blowfish_encrypt(input_buf, output_buf, &key);
        }
        write(fd_output, output_buf, sizeof(output_buf));
        memset(input_buf, 0, sizeof(input_buf));
    }
    close(fd_input);
    close(fd_output);
    free(output_file);
}

void encrypt_decrypt_folder(char *folder_path, char *key_arg_str)
{
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(folder_path)) == NULL)
    {
        perror("Error al abrir la carpeta");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char file_path[PATH_MAX];
        snprintf(file_path, sizeof(file_path), "%s/%s", folder_path, entry->d_name);

        encrypt_decrypt_file(file_path, key_arg_str);
    }

    closedir(dir);
}

int main(int argc, char **argv)
{
    create_directories();

    char *key_arg_str = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "dhfk:")) != -1)
    {
        switch (opt)
        {
        case 'd':
            dflag = true;
            break;
        case 'f':
            fflag = true;
            break;
        case 'h':
            print_help(argv[0]);
            return 0;
        case 'k':
            key_arg_str = optarg;
            break;
        case '?':
        default:
            fprintf(stderr, "uso: %s [-d] [-f] -k <key> <nombre_archivo|nombre_carpeta>\n", argv[0]);
            fprintf(stderr, "     %s -h\n", argv[0]);
            return 1;
        }
    }

    if (optind >= argc)
    {
        fprintf(stderr, "Especifique el nombre del archivo o carpeta.\n");
        fprintf(stderr, "uso: %s [-d] [-f] -k <key> <nombre_archivo|nombre_carpeta>\n", argv[0]);
        fprintf(stderr, "     %s -h\n", argv[0]);
        return 1;
    }

    char *input_path = argv[optind];

    if (!key_arg_str)
    {
        fprintf(stderr, "Error al especificar la clave de encriptación.\n");
        fprintf(stderr, "uso: %s [-d] [-f] -k <key> <nombre_archivo|nombre_carpeta>\n", argv[0]);
        fprintf(stderr, "     %s -h\n", argv[0]);
        return 1;
    }

    if (fflag)
    {
        encrypt_decrypt_folder(input_path, key_arg_str);
    }
    else
    {
        encrypt_decrypt_file(input_path, key_arg_str);
    }

    return 0;
}

