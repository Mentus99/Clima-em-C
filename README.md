# 🌦️ Clima em Tempo Real - Aplicativo Console em C

[![Licença MIT](https://img.shields.io/badge/Licença-MIT-blue.svg)](LICENSE)
[![Requisitos: MSYS2](https://img.shields.io/badge/Requisitos-MSYS2-green.svg)](https://www.msys2.org/)

Aplicativo de console que mostra dados meteorológicos em tempo real usando a API do OpenWeatherMap.

## 📋 Pré-requisitos
- [MSYS2](https://www.msys2.org/) instalado
- Compilador GCC (`pacman -S mingw-w64-ucrt-x86_64-gcc`)
- Biblioteca cURL (`pacman -S mingw-w64-ucrt-x86_64-curl`)
- [Chave da API OpenWeatherMap](https://home.openweathermap.org/api_keys) (grátis)

## 🚀 Configuração Rápida
```bash
# Clone o repositório
git clone https://github.com/G2bryel/Clima-em-C.git
cd Clima-em-C

# Configure sua API Key (edite o arquivo main.c)
# Substitua "SUA_CHAVE_AQUI" pela sua chave da API

# Compile e execute
compile.bat
```

## 🛠️ Como Usar
Execute o programa:

```bash
./clima.exe
```

Digite o nome da cidade quando solicitado (em inglês, substitua espaços por `_`):

```bash
Digite a cidade: Sao_Paulo
```

Veja os dados meteorológicos em tempo real:

## 📊 Exemplo de Saída
```plaintext
🌤️  APP DE CLIMA EM TEMPO REAL  🌤️

Digite a cidade: Rio_de_Janeiro

=== DADOS METEOROLÓGICOS ===
📍 Cidade: Rio_de_Janeiro
🌡️  Temperatura: 28.5°C
💧 Umidade: 70%
🌦️  Condição: Sunny
🤔 Sensação Térmica: 30.2°C
============================
```

## 🔧 Solução de Problemas

| Problema              | Solução |
|-----------------------|---------|
| Erro de compilação   | Verifique se o cURL está instalado (`pacman -S mingw-w64-ucrt-x86_64-curl`) |
| Dados incorretos     | Confira sua chave da API no OpenWeatherMap |
| Caracteres inválidos | Execute `chcp 65001` no terminal antes de rodar o programa |

## 📄 Licença
MIT License - Veja o arquivo [LICENSE](https://github.com/Mentus99/Clima-em-C/main/LICENSE.txt) para detalhes.

## 
✍️ [Gabriel Mendes](https://github.com/Mentus99)  
📧 [Entre em contato](mailto:gabriel.mendes.rodrigues@gmail.com)  
🐦 [Twitter](https://x.com/G2bryel)  

💡 Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests.

