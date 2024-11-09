#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 500
#define HEIGHT 500
#define GRID_SIZE 30


int tamanho_cobra = 5;
int cobrinha[100][2];
int sapinho[2];
bool bateu = false;
int direcao = 0; //0 = direita; 1 = cima; 2 = esquerda; 3 = baixo
float estrela[100][2];
int soma = 0;


void inicializaEstrelas(){
	for(int i= 0; i < 100; i++){
		estrela[i][0] = rand() % GRID_SIZE;
		estrela[i][1] = rand() % GRID_SIZE;
	}
	
}

void desenhaEstrelas(){
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POINTS);
	for(int i = 0; i<100; i++){
		glVertex2f(estrela[i][0], estrela[i][1]);
		
	}
	glEnd();
	
}


float gerarNumeroCor() {
	return rand() % RAND_MAX / (float)RAND_MAX;

}

void inicializarCobra(){
	//inicializar coordenadas do eixo X
	cobrinha[0][0] = 5;
	cobrinha[1][0] = 4;
	cobrinha[2][0] = 3;
	cobrinha[3][0] = 2;
	cobrinha[4][0] = 1;
	//inicializar coordenadas do eixo Y
	cobrinha[0][1] = 15;
	cobrinha[1][1] = 15;
	cobrinha[2][1] = 15;
	cobrinha[3][1] = 15;
	cobrinha[4][1] = 15;
	
	//inicializar o sapo
	sapinho[0] = rand() % GRID_SIZE;
	sapinho[1] = rand() % GRID_SIZE;
}


void desenhaCobrinha(int x, int y){
	
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x+1, y);
	glVertex2f(x+1, y+1);
	glVertex2f(x, y+1);
	glEnd();
}

void atualizacaoCobrinha(){
	for(int i = tamanho_cobra - 1; i > 0; i--){
		cobrinha[i][0] = cobrinha[i - 1][0];
		cobrinha[i][1] = cobrinha[i - 1][1];
	}
	if (direcao == 1){
		cobrinha[0][1]++;
	}
	if (direcao == 0){
		cobrinha[0][0]++;
	}
	if (direcao == 2){
		cobrinha[0][0]--;
	}
	if (direcao == 3){
		cobrinha[0][1]--;
	}
	
	//cobrinha[0][0]++;
	
}


void teclado(unsigned char tecla, int x, int y){
	switch (tecla){
		case 'w':
		case 'W':
			if(direcao != 3){
				direcao = 1;
			}
		break;
		case 'd':
		case 'D':
			if(direcao != 2){
				direcao = 0;
			}
		break;
		case 'a':
		case 'A':
			if(direcao != 0){
				direcao = 2;
			}
		break;
		case 's':
		case 'S':
			if(direcao != 1){
				direcao = 3;
			}
		break;
	}
}


void desenharSapo(){
	
	glColor3f(gerarNumeroCor(), gerarNumeroCor(), gerarNumeroCor());
	desenhaCobrinha(sapinho[0], sapinho[1]);
	
}

void exibirPontuacao(int score) {
 	char texto[20];
	 sprintf(texto, "Pontos: %d", score);
 	glColor3f(1.0, 1.0, 1.0); // Cor do texto
 	glRasterPos2f(1, GRID_SIZE - 2); // Posição do texto
 	for (char* c = texto; *c != '\0'; c++) {
 		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
 	}
}


void colisao(){
	if(cobrinha[0][0] < 0 || cobrinha[0][0] >= GRID_SIZE ||
	cobrinha[0][1] < 0 || cobrinha[0][1] >= GRID_SIZE){
		bateu = true;
	}
	
	if(cobrinha[0][0] == sapinho[0] && cobrinha[0][1] == sapinho[1]){
		tamanho_cobra = tamanho_cobra + 1;
		
		
		soma = soma + 10;
		
		
		sapinho[0] = rand() % GRID_SIZE;
		sapinho[1] = rand() % GRID_SIZE;
	}
		exibirPontuacao(soma);
	
	for(int i = 1; i < tamanho_cobra; i++){
		if(cobrinha[0][0] == cobrinha[i][0] && cobrinha[0][1] == cobrinha[i][1]){
			bateu = true;
		}
	}
		
	
}

void desenha(){
	int i;
	int soma = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	
	if(!bateu){
		
	for (i = 0; i < tamanho_cobra; i++){
		glColor3f(gerarNumeroCor(), gerarNumeroCor(), gerarNumeroCor());
		desenhaCobrinha(cobrinha[i][0], cobrinha[i][1]);
	}
	desenhaEstrelas();
	desenharSapo();
	atualizacaoCobrinha();
	colisao();
	}else {
		printf("Voce Perdeu!");
		exit(0);
	}

	glutSwapBuffers();
}



void timer(int value) {
	glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
    
}



void init() {
    glClearColor(0, 0, 0, 0); // Cor de fundo
    gluOrtho2D(0, GRID_SIZE, 0, GRID_SIZE); //define o tamanho do plano. 'GRID_SIZE' é ate onde o plano vai
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Inicializa o modo de exibição
    glutInitWindowSize(500, 500);                // Tamanho da janela
    glutCreateWindow("Transformações: Translação, Rotação, Escalonamento"); // Cria a janela

    init(); // Chama a função de inicialização
    inicializaEstrelas();
	inicializarCobra();
    glutDisplayFunc(desenha);
    //glutDisplayFunc(desenharSapo);
    //glutSpecialFunc(teclado);
	glutTimerFunc(100, timer, 0);    // Função de display
    glutKeyboardFunc(teclado);  // Função de teclado

    glutMainLoop(); // Entra no loop principal
    return 0;
}

