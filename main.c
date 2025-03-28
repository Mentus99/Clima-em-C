#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Estrutura para armazenar dados do clima
struct WeatherData {
    char cidade[50];
    float temperatura;
    int umidade;
    char condicao[50];
};

// Função para processar a resposta JSON (simplificada)
void parse_weather_json(const char* json, struct WeatherData* wd) {
    // Extrai dados básicos do JSON (implementação simplificada)
    char temp_str[10], humidity_str[10];
    
    // Extrai temperatura (em uma implementação real, use uma biblioteca JSON)
    const char* temp_ptr = strstr(json, "\"temp\":");
    if (temp_ptr) {
        sscanf(temp_ptr, "\"temp\":%f", &wd->temperatura);
    }
    
    // Extrai umidade
    const char* humidity_ptr = strstr(json, "\"humidity\":");
    if (humidity_ptr) {
        sscanf(humidity_ptr, "\"humidity\":%d", &wd->umidade);
    }
    
    // Extrai condição climática
    const char* main_ptr = strstr(json, "\"main\":\"");
    if (main_ptr) {
        sscanf(main_ptr, "\"main\":\"%49[^\"]", wd->condicao);
    }
}

// Callback para receber dados da API
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct WeatherData* wd = (struct WeatherData*)userp;
    
    // Processa o JSON recebido
    parse_weather_json((const char*)contents, wd);
    return realsize;
}

// Função principal
int main() {
    CURL* curl;
    CURLcode res;
    struct WeatherData clima = {0};
    
    // Configuração inicial
    printf("🌤️ App de Clima em Tempo Real 🌤️\n");
    printf("Digite sua cidade: ");
    scanf("%49s", clima.cidade);
    
    // Inicializa cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    if(curl) {
        char url[256];
        const char* api_key = "cdb136214fedd37bcd6d553b3ce8fc14"; // Substitua pela sua chave
        
        // Monta a URL da API
        snprintf(url, sizeof(url), 
                "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric&lang=pt",
                clima.cidade, api_key);
        
        // Configura a requisição
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &clima);
        
        // Executa a requisição
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            fprintf(stderr, "Erro na requisição: %s\n", curl_easy_strerror(res));
        } else {
            // Exibe os resultados
            printf("\n=== Dados do Clima ===\n");
            printf("Cidade: %s\n", clima.cidade);
            printf("Temperatura: %.1f°C\n", clima.temperatura);
            printf("Umidade: %d%%\n", clima.umidade);
            printf("Condição: %s\n", clima.condicao);
            printf("======================\n");
        }
        
        // Limpeza
        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
    return 0;
}