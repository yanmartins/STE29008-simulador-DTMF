# Projeto Final

Projeto final de Sistemas Embarcados (STE29008) do curso de Engenharia de Telecomunicações do Instituto Federal de Santa Catarina - câmpus São José, realizada em 2019.1.

## Implementação de um simulador DTMF a partir do CI HM 91710 presente no telefone Premium Intelbras

Este projeto consiste na implementação de bibliotecas para um simulador de tons DTMF, destinadas ao Arduino MEGA 2560. Essas bibliotecas foram implementadas utilizando a linguagem de programação C++ e a biblioteca AVR-Libc.

### Introdução ao projeto

O sistema possui um teclado matricial para a inserção e cadastros de sequências, um display LCD 16x2 para exibição dos estados, um telefone Premium Intelbras com um CI HM 91710 gerador de tons DTMF e um Arduino MEGA 2560. Conforme diagrama de blocos visto na figura abaixo:

![Diagrama de blocos](https://github.com/yanmartins/STE29008-simulador-DTMF/blob/master/imagens/diagrama_de_blocos.PNG)

Há também, um LED, que quando apagado, indica que o sistema está executando uma operação, seja ela discar ou carregar os menus de opção. E quando está piscando, significa que o sistema está aguardando a entrada de dados através do teclado por parte do usuário.

Para testes, é utilizado o Adaptador VoIP para Telefone Analógico GKM 2000T, também da Intelbras (FXS).
