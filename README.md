# LightCaster 2D

**LightCaster 2D** é um simulador interativo de propagação de luz em 
tempo real que demonstra visualmente os princípios fundamentais da 
óptica geométrica em um ambiente bidimensional. Ele permite explorar 
como a luz se propaga em linha reta e interage com diferentes 
obstáculos, criando padrões de iluminação e sombra.



## 📜 Conceitos Físicos Demonstrados

O simulador ilustra diversos conceitos importantes da física óptica:

- **Propagação retilínea da luz**: Demonstra como a luz viaja em linha reta em um meio homogêneo.
- **Formação de sombras**: Visualiza como objetos opacos bloqueiam a passagem da luz.
- **Propagação radial**: Mostra como a luz emana de uma fonte pontual em todas as direções.
- **Oclusão**: Ilustra como objetos mais próximos da fonte bloqueiam a luz que chegaria a objetos mais distantes.

## 🛠️ Características Principais

- **Fonte de luz controlada pelo mouse** 🎯: A fonte luminosa segue o cursor do mouse em tempo real.
- **Obstáculos variados** 🏗️: Paredes e retângulos estáticos, além de um círculo dinâmico em movimento elíptico.
- **Visualização de raios** 🔦: Representação dos caminhos dos raios de luz e suas interseções com obstáculos.
- **Simulação em tempo real** ⚡: Cálculos eficientes para atualização instantânea da iluminação e sombras.

## 🎓 Aplicações Educacionais

O **LightCaster 2D** pode ser usado para:

- Ensino de conceitos básicos de óptica geométrica.
- Demonstração visual de princípios da propagação da luz.
- Introdução a algoritmos de *ray casting*.
- Exploração interativa dos efeitos de sombra e iluminação.

## 💻 Aspectos Técnicos

O projeto é desenvolvido em **C++** utilizando a biblioteca **SFML (Simple and Fast Multimedia Library)**. Ele implementa algoritmos eficientes para:

- Cálculo de interseção **raio-linha**.
- Cálculo de interseção **raio-círculo**.
- Renderização otimizada de múltiplos raios de luz.
- Interação em tempo real com entrada do usuário.

## 🔄 Extensibilidade

O **LightCaster 2D** possui uma arquitetura modular que permite futuras extensões, incluindo:

- Diferentes tipos de fontes luminosas (**direcional, cônica, etc.**).
- Materiais com propriedades ópticas avançadas (**reflexão, refração, difração**).
- Interfaces gráficas para ajuste de parâmetros.
- Cenários pré-configurados para demonstrar fenômenos ópticos específicos.

## 🚀 Instalação e Execução

### 🔧 Requisitos

- **Sistema Operacional**: Windows, Linux ou macOS
- **Compilador C++** compatível com **C++17** ou superior
- **Biblioteca SFML 2.5+** instalada


## Demonstração

<video width="800" controls>
  <source src="src/assets/records/recording.mp4" type="video/mp4">
  Seu navegador não suporta vídeos.
</video>