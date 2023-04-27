# include "AIPlayer.h"
# include "Parchis.h"

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 4;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta

bool AIPlayer::move(){
    cout << "Realizo un movimiento automatico" << endl;
    
    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    cout << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color & c_piece, int & id_piece, int & dice) const{
    // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente 
    //como lo que se muestran al final de la función.
    
    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores, 
    //respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    // // El color de ficha que se va a mover
    // c_piece = actual->getCurrentColor();

    // // Vector que almacenará los dados que se pueden usar para el movimiento
    // vector<int> current_dices;
    // // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    // vector<int> current_pieces;

    // // Se obtiene el vector de dados que se pueden usar para el movimiento
    // current_dices = actual->getAvailableDices(c_piece);
    // // Elijo un dado de forma aleatoria.
    // dice = current_dices[rand() % current_dices.size()];

    // // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    // current_pieces = actual->getAvailablePieces(c_piece, dice);

    // // Si tengo fichas para el dado elegido muevo una al azar.
    // if(current_pieces.size() > 0){
    //     id_piece = current_pieces[rand() % current_pieces.size()];
    // }
    // else{
    //     // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
    //     id_piece = SKIP_TURN;
    // }

    
    // El siguiente código se proporciona como sugerencia para iniciar la implementación del agente.

    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = menosinf, beta = masinf; // Cotas iniciales de la poda AlfaBeta
    // Llamada a la función para la poda (los parámetros son solo una sugerencia, se pueden modificar).
    //valor = Poda_AlfaBeta(*actual, jugador, 0, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
    // cout << "Valor PodaAlfaBeta: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    // ----------------------------------------------------------------- //

    // Si quiero poder manejar varias heurísticas, puedo usar la variable id del agente para usar una u otra.
    switch(id){
        case 0:
            valor = Poda_AlfaBeta(*actual, jugador, 0, c_piece, id_piece, dice, alpha, beta, Heuristica);
            break;
        case 1:
            valor = Poda_AlfaBeta(*actual, jugador, 0, c_piece, id_piece, dice, alpha, beta, Heuristica);
            break;
        case 2:
            valor = Poda_AlfaBeta(*actual, jugador, 0, c_piece, id_piece, dice, alpha, beta, Heuristica);
            break;
    }
    cout << "Valor Poda_AlfaBeta: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    
}



double AIPlayer::ValoracionTest(const Parchis &estado, int jugador)
{
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_jugador += 5;
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}


void AIPlayer::thinkAleatorio(color & c_piece,int &id_piece,int &dice) const{

    // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente 
    //como lo que se muestran al final de la función.
    
    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores, 
    //respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    // El color de ficha que se va a mover
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);
    // Elijo un dado de forma aleatoria.
    dice = current_dices[rand() % current_dices.size()];

    // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    current_pieces = actual->getAvailablePieces(c_piece, dice);

    // Si tengo fichas para el dado elegido muevo una al azar.
    if(current_pieces.size() > 0){
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
    else{
        // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
        id_piece = SKIP_TURN;
    }
}

void AIPlayer::thinkAleatorioMasInteligente(color & c_piece,int &id_piece,int &dice)const {
    //El color de la ficha que se va a mover
    c_piece = actual->getCurrentColor();

    //vector que almacenara los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    //vector que almacenara los ids de las fichas que se pueden mover para el dado elegido.
    vector<int> current_pieces;
    //se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);

    //En vez de elegir un dado al azar, miro primero cuales tienen fichas que se pueden mover.
    vector<int> current_dices_que_pueden_mover_ficha;
    for(int i = 0;i<current_dices.size();i++){
        //Se obtiene el vector de fichas que se  pueden mover para el dado objetivo.
        current_pieces =  actual->getAvailablePieces(c_piece,current_dices[i]);

        //si se pueden mover fichas para el dado actual, lo añado al vector de dados mover fichas.
        if(current_dices.size() > 0){
            current_dices_que_pueden_mover_ficha.push_back(current_dices[i]);
        }
    }

    //Si no tengo ningun dado que pueda mover fichas, paso turno con un dado al azar (la macro SKIP_TURN me permite no mover)
    if(current_dices_que_pueden_mover_ficha.size() == 0){
        dice =  current_dices[rand() % current_dices.size()];
        id_piece = SKIP_TURN;
    }else{// en caso contrario, elijo un dado  de forma aleatoria de entre los que pueden mover ficha.
        dice = current_dices_que_pueden_mover_ficha[rand() % current_dices_que_pueden_mover_ficha.size()];
        //Se obtiene el vector de fichas que se pueden mover para el dado elejido
        current_pieces =  actual->getAvailablePieces(c_piece,dice);
        //Muevo una ficha al azar de entre las que se pueden mover
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
}

void AIPlayer::thinkFichaMasAdelantada(color & c_piece,int &id_piece,int &dice)const {
    //Elijo el dado haciendo lo mismo que el jugador anterior
    thinkFichaMasAdelantada(c_piece,id_piece,dice);
    //Tras llamar a esta funcion, ya tengo en dice el numero de dado que quiero usar.
    //ahora en vez de mover una ficha al azar, voy a mover la que este mas adelantada
    // (equivalentemente, la mas cercana a la meta)

    vector<int> current_pieces = actual->getAvailablePieces(c_piece,dice);

    int id_ficha_mas_adelantada = -1;
    int min_distancia_meta = 9999;
    for(int i=0;i<current_pieces.size();i++){
        //distanciaToGoal(color,id) devuelve la distancia a la meta de la ficha [id] del color que indicque.
        int distancia_meta = actual->distanceToGoal(c_piece,current_pieces[i]);
        if(distancia_meta < min_distancia_meta){
            min_distancia_meta = distancia_meta;
            id_ficha_mas_adelantada = current_pieces[i];
        }
    }

    // SI no he encontrado ninguna ficha, paso turno.
    if(id_ficha_mas_adelantada == -1){
        id_piece = SKIP_TURN;
    }else{//En caso contrario, movere la ficha mas adelantada
        id_piece = id_ficha_mas_adelantada;
    }
}

void AIPlayer::thinkMejorOpcion(color & c_piece,int &id_piece,int &dice)const {
    // Vamos a mirar todos los posibles movimientos del jugador actual accediendo a los hijos del estado actual

    //generateNextMove va iterando sobre cada hijo. Le paso la accion del ultimo movimiento sobre el que he iterado y me devolvera el siguiente. Inicialmente,cuando aun no he hecho ningun
    //movimiento, lo inicializo asi.
    color last_c_piece = none; // El color de la ultima ficha que se movio
    int last_id_piece = -1; // el id de la ultima ficha que se movio
    int last_dice = -1; // el dado que se uso en el ultimo movimiento

    //Cuando ya he recorrido todos los hijos, la funcion devuelve el estado actual.De esta forma puedo saber
    //cuando para de iterar.

    Parchis siguiente_hijo = actual->generateNextMove(last_c_piece,last_id_piece,last_dice);

    bool me_quedo_con_esta_accion = false;

    while(!(siguiente_hijo == *actual) && !me_quedo_con_esta_accion){
        if(siguiente_hijo.isEatingMove() or siguiente_hijo.isGoalMove() or (siguiente_hijo.gameOver() and siguiente_hijo.getWinner() == this->jugador)){
            //Me quedo con la accion actual ( se almaceno en last_c_piece, las_id_piece, las_dice al llamar generateNextMove)
            me_quedo_con_esta_accion =true;
        }else{
            //Genero el siguiente hijo
            siguiente_hijo = actual->generateNextMove(last_c_piece,last_id_piece,last_dice);
        }
    }
    //SI he encontrado una accion que me interesa, la guardo en las variables pasadas por referencia
    if(me_quedo_con_esta_accion){
        c_piece = last_c_piece;
        id_piece = last_id_piece;
        dice = last_dice;
    }else{
        thinkFichaMasAdelantada(c_piece,id_piece,dice);
    }

}

double AIPlayer::Poda_AlfaBeta(const Parchis &actual, int jugador, int profundidad, color &c_piece, int &id_piece, int &dice, double alpha, double beta, double (*heuristic)(const Parchis &, int))const {

    if(profundidad == PROFUNDIDAD_ALFABETA or actual.gameOver()){ //No hace falta introducir la constante global PROFUNDIDAD_ALFABETA, como parametro ya que se puede acceder directamente
        return heuristic(actual,jugador);                         // Una vez llegamos a las hojas, sacamos el valor del nodo y lo comparamos con su correspondiente intervalo
                                                                  // Esto lo hara tantas veces como nodos terminales haya, excepto que se pode alguna rama.
    }

    color last_c_piece = none; // El color de la ultima ficha que se movio
    int last_id_piece = -1; // el id de la ultima ficha que se movio
    int last_dice = -1; // el dado que se uso en el ultimo movimiento
    double valor_aux; // Valor para comparar tanto con alfa como con beta
    

    Parchis siguiente_hijo = actual.generateNextMoveDescending(last_c_piece,last_id_piece,last_dice);

    //Calculamos el PODA ALFA-BETA
    if(jugador == actual.getCurrentPlayerId() ){// es decir es un nodo MAX ya que los nodos MAX son pares.
        while(!(siguiente_hijo == actual)){
            
            valor_aux = Poda_AlfaBeta(siguiente_hijo,jugador,profundidad+1,c_piece,id_piece,dice,alpha,beta,heuristic);
            
            if(valor_aux>alpha ){
                alpha = valor_aux; //Ya que queremos coger el valor MAXIMO de cada nodo
                if(profundidad == 0){
                    c_piece = last_c_piece; //Si es le MAX principal guardamos el movimiento que deseamos
                    id_piece = last_id_piece;
                    dice = last_dice;
                }
                
            }
            if(alpha >= beta){ //Comprobacion de poda para hacer mas eficiente el algoritmo
                break;
            }

            siguiente_hijo = actual.generateNextMoveDescending(last_c_piece,last_id_piece,last_dice); // genero el siguiente hijo hasta que la profundida = ProfundidadLAFABETA, ya que sera el final.
            //Genero el hijo con Descending ya que el criterio de poda se hace mas eficiente ya que poda mas y no se pierde tiempo analizando nodos que no lo son


            // if(siguiente_hijo.isEatingMove() or siguiente_hijo.isGoalMove() or (siguiente_hijo.gameOver() and siguiente_hijo.getWinner() == this->jugador)){
            //     //Me quedo con la accion actual ( se almaceno en last_c_piece, las_id_piece, las_dice al llamar generateNextMove)
            //     me_quedo_con_esta_accion =true;
            // }else{
            //     //Genero el siguiente hijo
            //     siguiente_hijo = actual->generateNextMove(last_c_piece,last_id_piece,last_dice);
            // }
        }
        return alpha;
    }else{ // es un nodo MIN
        while(!(siguiente_hijo == actual)){
            
            valor_aux = Poda_AlfaBeta(siguiente_hijo,jugador,profundidad+1,c_piece,id_piece,dice,alpha,beta,heuristic);
            
            if(valor_aux<beta ){
                beta = valor_aux;//Ya que queremos coger el valor MINIMO de cada nodo. No hace falta guardar el movimiento ya que es el MAX el que tiene profundidad = 0.
            }
            
            if(alpha >= beta){
                break; // No guardamos las variables a diferencia del nodo MAX ya que solo necesitamos el movimiento en el MAX, ya que es profundidad = 0.
            } // como no es el nodo max, no hace falta guardarlo en c_piece y sus correspondientes ya que por parametro los recuperaremos una vez llegue al nodo terminal.

            siguiente_hijo = actual.generateNextMoveDescending(last_c_piece,last_id_piece,last_dice); // genero el siguiente hijo hasta que la profundida = ProfundidadLAFABETA, ya que sera el final.
            //Se hace igual que el MAX pero comprobando que valor_aux sea menor que beta y devolviendo al final del if, beta en vez de alpha. Ya que queremos ir cogiendo 
            // el minimo valor de los maximos para asi sacar el MINIMAX y a su vez podar en el caso de que cumpla la condicion de PODA ( a >= b )
        }
        
        return beta;
    }
    
}

double AIPlayer::Heuristica(const Parchis &estado, int jugador)
{
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }else{
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        double puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j)) //Queremos que no tener peligro por lo que queremos siempre estar en una casilla segura ante todo.
                {
                    puntuacion_jugador += 5;
                }
                if (estado.getBoard().getPiece(c, j).type == goal) //Queremos que llegue al final y meta la ficha, por lo que le damos importancia.
                {
                    puntuacion_jugador += 10;
                }
                if (estado.getBoard().getPiece(c, j).type == home) //No queremos que este en casa ninguna ficha por lo que le restamos valor, asi
                                                                    // en el momento que nos coma, sera peor el valor heuristico.
                {
                    puntuacion_jugador -= 20;
                }
                // if(distancia_promedio(c,estado) == j ){
                //     puntuacion_jugador += 6;
                // }
                
                puntuacion_jugador += 100 - estado.distanceToGoal(c,j);//Lo mas importante de todo, dependiendo de donde estemos posicionados, nos dara mejor
                                                                    // o peor heuristica, por lo que al numero de casillas totales le restamos la distancia que estamos
                                                                    // de la meta y nos dara un valor diferente en cada casilla. Por lo que cuanto mas alante podamos y
                                                                    // cumpla el resto de reglas mejor.
                
            }
            if(estado.isEatingMove() and estado.getCurrentPlayerId() == jugador){
                if(estado.eatenPiece().first == my_colors[(i+1)%2]){
                    puntuacion_jugador += 9;
                }else{
                    puntuacion_jugador += 15;
                }
            }
        }
        
        
        

        // Recorro todas las fichas del oponente
        double puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            
            for (int j = 0; j < num_pieces; j++)
            {
                
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_oponente += 5;
                }
                if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_oponente += 10;
                }
                if (estado.getBoard().getPiece(c, j).type == home)
                {
                    puntuacion_oponente -= 20;
                }
                
                puntuacion_oponente += 100 - estado.distanceToGoal(c,j);
            }
            if(estado.isEatingMove() and estado.getCurrentPlayerId() == oponente){
                if(estado.eatenPiece().first == op_colors[(i+1)%2]){
                    puntuacion_jugador += 9;
                }else{
                    puntuacion_jugador += 15;
                }
            }
        }
        // if(estado.isEatingMove() and estado.getCurrentPlayerId() == oponente){
        //     puntuacion_oponente += 9;
        // }
        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente; //Para calcular el valor, a la puntuacion mia le resto la del oponente.
    }
}

// int AIPlayer::distancia_promedio(color colores,const Parchis &estado){
//     int valor_aux = estado.distanceToGoal(colores,0);
//     int pieza = 0;
//     for( int i=1 ; i<4 ; i++){
//         int valor = estado.distanceToGoal(colores,i);
//         if(valor < valor_aux){
//             valor_aux = valor;
//             pieza = i;
//         }
//     }
//     return pieza;
// }

// bool AIPlayer::ComerFicha(color c,const Parchis &estado){
//     pair<color, int> aux ;
//     aux.second = estado.eatenPiece().second;
//     aux.first = estado.eatenPiece().first;
//     if(aux.first != none){
//         return true;
//     }else{
//         return false;
//     }
// }