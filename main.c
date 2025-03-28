#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <windows.h>

// Estrutura para armazenar dados da resposta HTTP
typedef struct {
    char *data;
    size_t size;
} ResponseData;

// Callback para escrever os dados recebidos
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    ResponseData *mem = (ResponseData *)userp;

    char *ptr = realloc(mem->data, mem->size + realsize + 1);
    if(!ptr) return 0;

    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = '\0';
    return realsize;
}

// Função para extrair valores do JSON
void extract_json_value(const char *json, const char *key, char *output, int max_len) {
    char search_str[50];
    sprintf(search_str, "\"%s\":", key);
    
    const char *start = strstr(json, search_str);
    if (!start) {
        output[0] = '\0';
        return;
    }
    
    start += strlen(search_str);
    while (*start == ' ' || *start == '\"' || *start == ':') start++;
    
    int i = 0;
    while (i < max_len - 1 && start[i] != ',' && start[i] != '}' && start[i] != '\"') {
        output[i] = start[i];
        i++;
    }
    output[i] = '\0';
}

// Configura o console para UTF-8
void setup_console() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

// Função para exibir erros em vermelho
void print_error(const char *message) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12); // Vermelho
    printf("%s\n", message);
    SetConsoleTextAttribute(hConsole, 7); // Volta ao normal
}

int main() {
    setup_console();
    
    CURL *curl;
    CURLcode res;
    ResponseData chunk = {0};
    char cidade[50];
    const char *api_key = "cdb136214fedd37bcd6d553b3ce8fc14"; // Sua chave
    
    // Interface inicial
    printf("================================\n");
    printf("    APP DE CLIMA EM TEMPO REAL   \n");
    printf("================================\n\n");
    printf("Digite a cidade (ex: Brasilia): ");
    
    if (scanf("%49s", cidade) != 1) {
        print_error("Erro ao ler a cidade.");
        return 1;
    }

    // Inicializa cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    if(curl) {
        char url[256];
        snprintf(url, sizeof(url), 
                "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric&lang=pt",
                cidade, api_key);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); // Timeout de 10 segundos

        printf("\nObtendo dados...\n");
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            print_error(curl_easy_strerror(res));
        } else if (chunk.data) {
            // Extrai dados do JSON
            char temp[10], humidity[10], desc[50], feels_like[10];
            
            extract_json_value(chunk.data, "temp", temp, sizeof(temp));
            extract_json_value(chunk.data, "humidity", humidity, sizeof(humidity));
            extract_json_value(chunk.data, "description", desc, sizeof(desc));
            extract_json_value(chunk.data, "feels_like", feels_like, sizeof(feels_like));
            
            // Exibe resultados formatados
            printf("\n=== DADOS METEOROLÓGICOS ===\n");
            printf("📍 Cidade: %s\n", cidade);
            printf("🌡️  Temperatura: %s°C\n", temp);
            printf("💧 Umidade: %s%%\n", humidity);
            printf("🌦️  Condição: %s\n", desc);
            printf("🤔 Sensação Térmica: %s°C\n", feels_like);
            printf("============================\n");
        } else {
            print_error("Nenhum dado recebido da API.");
        }
        
        // Limpeza
        if(chunk.data) free(chunk.data);
        curl_easy_cleanup(curl);
    } else {
        print_error("Falha ao inicializar cURL.");
    }
    
    curl_global_cleanup();
    
    printf("\nPressione ENTER para sair...");
    getchar();
    getchar();
    return 0;
}