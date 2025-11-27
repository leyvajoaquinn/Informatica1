/*
  Trabajo Práctico Info I
  Proyecto: Bot de Telegram en C
  URL: https://github.com/usuario/proyecto-bot
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <curl/curl.h>

struct memory {
    char *response;
    size_t size;
};

static size_t cb(char *data, size_t size, size_t nmemb, void *clientp) {
    size_t realsize = size * nmemb;
    struct memory *mem = clientp;
    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(!ptr) return 0;
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;
    return realsize;
}
void respuesta(CURL *curl, const char *token, long long chat_id, const char *mensaje, const char *nombre);
void registrar(const char *nombre, const char *mensaje);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s token.txt\n", argv[0]);
        return 1;
    }

    char token[128];
    FILE *f = fopen(argv[1], "r");
    if (!f) { perror("No se pudo abrir archivo"); return 1; }
    fgets(token, sizeof(token), f);
    fclose(f);
    token[strcspn(token, "\n")] = 0;

    CURL *curl = curl_easy_init();
    if(!curl) return 1;

    int offset = 0;
    while (1) {
        
        char api_url[512];
        snprintf(api_url, sizeof(api_url),
                 "https://api.telegram.org/bot%s/getUpdates?offset=%d",
                 token, offset);

        struct memory chunk = {NULL , 0};
        curl_easy_setopt(curl, CURLOPT_URL, api_url);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
         CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            printf("Error Código: %d\n", res);
            sleep(2);
            continue;
        }

    if (res == 0 && chunk.response) {
            char mensaje[256] = {0};
            char nombre[128] = {0};
            printf("Respuesta JSON:\n%s\n", chunk.response);

            char *update_ptr = strstr(chunk.response, "\"update_id\":");
        if (update_ptr) {
            update_ptr += strlen("\"update_id\":");
            int id_update;
            sscanf(update_ptr, "%d", &id_update);
            offset = id_update + 1;
            printf("update_id = %d\n", id_update);
        }
            long long chat_id = 0;
            char *chatptr = strstr(chunk.response, "\"chat\"");
        if (chatptr) {
            char *idptr = strstr(chatptr, "\"id\":");
        if (idptr) {
            idptr += strlen("\"id\":");
            sscanf(idptr, "%lld", &chat_id);
            printf("chat.id = %lld\n", chat_id);
            }
        }
        char *textptr = strstr (chunk.response, "\"text\":");
        if(textptr){
            textptr += strlen( "\"text\":");
            sscanf(textptr,  "\"%255[^\"]\"",mensaje);
            printf("mensaje.text = %s\n",mensaje);
        }
        char *nameptr = strstr(chunk.response, "\"first_name\":");
        if(nameptr){
            nameptr += strlen("\"first_name\":");
            sscanf(nameptr,"\"%127[^\"]\"",nombre);
            printf("chat.first_name = %s\n",nombre);

        }
        respuesta(curl, token, chat_id, mensaje, nombre);
        registrar(nombre, mensaje);


    }

        sleep(2);
    }

    curl_easy_cleanup(curl);
    return 0;
}

void respuesta(CURL *curl, const char *token, long long chat_id, const char *mensaje, const char *nombre) {
    if (strlen(mensaje) == 0 || chat_id == 0) return;
    char texto[256];
    char reply_url[512];

   if (strcmp(mensaje, "hola") == 0) {
        snprintf(texto, sizeof(texto), "Hola%%20%s%%21%%2C%%20buenos%%20dias.", nombre);
    } else if (strcmp(mensaje, "chau") == 0) {
        snprintf(texto, sizeof(texto), "Chau%%20%s%%2C%%20nos%%20vemos.", nombre);
    } else {
        snprintf(texto, sizeof(texto), "No%%20entiendo%%20tu%%20mensaje%%2C%%20pero%%20estoy%%20aprendiendo.");
    }

    snprintf(reply_url, sizeof(reply_url),
             "https://api.telegram.org/bot%s/sendMessage?chat_id=%lld&text=%s",
             token, chat_id, texto);


    struct memory chunk = {NULL, 0};
    curl_easy_setopt(curl, CURLOPT_URL, reply_url);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    CURLcode res2 = curl_easy_perform(curl);
    if (res2 != CURLE_OK) {
        printf("Error al enviar mensaje: %d\n", res2);
    } else {
        printf("Mensaje enviado en respuesta a: %s\n", mensaje);
    }

    free(chunk.response);
}

void registrar(const char *nombre, const char *mensaje) {
    FILE *log = fopen("registro.txt", "a"); 
    if (!log) {
        perror("No se pudo abrir registro.txt");
        return;
    }

    time_t ahora = time(NULL);
    struct tm *t = localtime(&ahora);

    fprintf(log, "[%02d:%02d:%02d] %s: %s\n",
            t->tm_hour, t->tm_min, t->tm_sec,
            nombre, mensaje);

    fclose(log);
}
