package ProjetAPO;

import java.util.Scanner;
public class Grid3D {

    private int sizeGrid;
    private int nbGrid;

    private Grid[] tableauGrid; //Tableau de grilles (il y aura sizeGrid grilles dans ce tableau)

    private boolean endGame;
    private boolean endGameProfondeur;

    private int turn;

    public Grid3D() {
        sizeGrid = 3;
        nbGrid = 3;
        this.endGame = false;
        tableauGrid = new Grid[nbGrid];
        for (int i = 0; i < nbGrid; i++) {
            Grid grid = new Grid();
            tableauGrid[i] = grid;
        }
    }

    public Grid3D(int sizeN) {
        sizeGrid = sizeN;
        nbGrid = sizeGrid;
        this.endGame = false;
        tableauGrid = new Grid[nbGrid];
        for (int i = 0; i < nbGrid; i++) {
            Grid grid = new Grid(sizeGrid);
            tableauGrid[i] = grid;
        }
    }

    public void displayGrid3D() {
        char letterIndGrid;
        int counter = 96;
        for (int i = 0; i < nbGrid; i++) {
            counter++;
            letterIndGrid = (char) counter;
            System.out.println("Grille (" + letterIndGrid + ")");
            tableauGrid[i].displayGrid();
        }
    }


    public void pickNumber3D(int player){
        boolean verify;
        System.out.println("tour de " + player);
        displayGrid3D();
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("Choose the Grid that you want to fill : ");
            char letterGrid = scanner.next().charAt(0);
            int ascii = (int)letterGrid - 97;

            if (ascii >=0 && ascii < nbGrid) { //if the ascii code of the character input, is between the code ascii of 'a' and
                //the last letter of our grid then we can continue
                verify = verifyEntryGrid();
                if(verify){
                    tableauGrid[ascii].pickNumber(player);
                    break;
                }
            } else {
                System.out.println("Invalid input.");
            }

        }
        turn ++;
    }

    public void displayWinningLine3D(int line, int column){
        String player;
        if(turn % 2 == 0) {
            player = "O";
        }else{;
            player = "X";
        }

        for (int i = 0; i < sizeGrid; i++) {
            tableauGrid[i].getTable()[line][column] = "[" + player + "]";
        }
        displayGrid3D();
    }

    public void displayWinningVerticalDiagonal3D(String pos, int column){
        String player;
        if(turn % 2 == 0) {
            player = "O";
        }else{;
            player = "X";
        }
        if (pos.equals("t")) {
            for (int i = 0; i < sizeGrid; i++) {
                tableauGrid[i].getTable()[i][column] = "[" + player + "]";
            }
            displayGrid3D();
        }
        else if (pos.equals("b")) {
            for (int i = 0; i < sizeGrid; i++) {
                tableauGrid[i].getTable()[sizeGrid - i - 1][column] = "[" + player + "]";
            }
            displayGrid3D();
        }
    }


    public void displayWinningHorizontalDiagonal3D(String pos, int line){
        String player;
        if(turn % 2 == 0) {
            player = "O";
        }else{;
            player = "X";
        }
        if (pos.equals("l")) {
            for (int i = 0; i < sizeGrid; i++) {
                tableauGrid[i].getTable()[line][i] = "[" + player + "]";
            }
            displayGrid3D();
        }
        else if (pos.equals("r")) {
            for (int i = 0; i < sizeGrid; i++) {
                tableauGrid[i].getTable()[line][sizeGrid - i - 1]= "[" + player + "]";
            }
            displayGrid3D();
        }
    }


    public void displayWinningBasicDiagonal3D(String pos){
        String player;
        if(turn % 2 == 0) {
            player = "O";
        }else{;
            player = "X";
        }
        if (pos.equals("ltf")) {
            for (int i = 0; i < sizeGrid; i++) {
                tableauGrid[i].getTable()[i][i] = "[" + player + "]";
            }
            displayGrid3D();
        }
        else if (pos.equals("lbf")) {
            for (int i = 0; i < sizeGrid; i++) {
                tableauGrid[i].getTable()[sizeGrid - i - 1][i]= "[" + player + "]";
            }
            displayGrid3D();
        }
        else if (pos.equals("rtf")) {
            for (int i = 0; i < sizeGrid; i++) {
                tableauGrid[i].getTable()[i][sizeGrid - i - 1]= "[" + player + "]";
            }
            displayGrid3D();
        }
        else if (pos.equals("rbf")) {
            for (int i = 0; i < sizeGrid; i++) {
                tableauGrid[i].getTable()[sizeGrid - i - 1][sizeGrid - i - 1]= "[" + player + "]";
            }
            displayGrid3D();
        }
    }

    public boolean verifyEntryGrid(){
        Scanner scanner = new Scanner(System.in);
        String input;
        while (true) {
            System.out.print("Are you sure ? Y/N");
            input = scanner.next();

            if (input.equals("Y") || input.equals("N") || input.equals("n") || input.equals("y")) {
                break;
            } else {
                System.out.println("Invalid input. Please enter Y or N.");
            }
        }
        if (input.equals("Y") || input.equals("y")){
            return true;
        }
        else {
            return false;
        }
    }

    public boolean checkForWinner3D(){

        for(int i=0; i<nbGrid; i++){
            endGame = tableauGrid[i].checkForWinner();
            if(endGame){
               /* char letterGrid = (char)(i + 97);
                System.out.println("Victoire sur grille " + letterGrid);*/
                break;
            }
        }
        endGameProfondeur = checkWinProfondeur();
        if(endGameProfondeur){
            endGame = endGameProfondeur;
        }
        return endGame;
    }

    public boolean checkWinProfondeur(){

        //Check on a straight deep line
        for (int i = 0; i < sizeGrid; i++) { //Loop line by line
            for (int j = 0; j < sizeGrid; j++) {
                for(int k=0; k<nbGrid - 1; k++){ //Loop Grid by Grid
                    endGameProfondeur = tableauGrid[k].getTable()[i][j] == tableauGrid[k+1].getTable()[i][j];
                    //End of Game = true when 2 cells are equal, false if not
                    if(!endGameProfondeur) { //If 2 cells not equal, break loop
                        //System.out.println("Line " + i + " - Cases " + j + " & " + (j+1) + " not good."); //Test : to REMOVE later
                        break;
                    }
                }
                if(endGameProfondeur) { //After a line, if endgame is still true, win detected
                    int indice = sizeGrid * i + (j + 1);
                    System.out.println("### Win detected on deep line " + indice + " ###");
                    displayWinningLine3D(i, j);
                    return endGameProfondeur;
                }
            }
        }

        //Check on a vertical deep diagonal on a line from top to bottom
        for (int i = 0; i < sizeGrid; i++) { //Loop line by line
            for (int j = 0; j < nbGrid - 1; j++) {
                endGameProfondeur = tableauGrid[j].getTable()[j][i] == tableauGrid[j+1].getTable()[j+1][i];
                //End of Game = true when 2 cells are equal, false if not
                if(!endGameProfondeur) { //If 2 cells not equal, break loop
                    //System.out.println("Line " + i + " - Cases " + j + " & " + (j+1) + " not good."); //Test : to REMOVE later
                    break;
                }
            }
            if(endGameProfondeur) { //After a line, if endgame is still true, win detected
                System.out.println("### Win detected on vertical deep diagonal (top to bot) ###");
                displayWinningVerticalDiagonal3D("t", i);
                return endGameProfondeur;
            }
        }

        //Check on a vertical deep diagonal on a line from bottom to top
        for (int i = 0; i < sizeGrid; i++) { //Loop line by line
            for (int j = 0; j < sizeGrid - 1; j++) {
                endGameProfondeur = tableauGrid[j].getTable()[sizeGrid-1-j][i] == tableauGrid[j+1].getTable()[sizeGrid-2-j][i];
                //End of Game = true when 2 cells are equal, false if not
                if(!endGameProfondeur) { //If 2 cells not equal, break loop
                    //System.out.println("Line " + i + " - Cases " + j + " & " + (j+1) + " not good."); //Test : to REMOVE later
                    break;
                }
            }
            if(endGameProfondeur) { //After a line, if endgame is still true, win detected
                System.out.println("### Win detected on vertical deep diagonal (bot to top) ###");
                displayWinningVerticalDiagonal3D("b", i);
                return endGameProfondeur;
            }
        }

        //Check on a horizontal deep diagonal from left to right
        for (int i = 0; i < sizeGrid; i++) { //Loop line by line
            for (int j = 0; j < sizeGrid - 1; j++) {
                endGameProfondeur = tableauGrid[j].getTable()[i][j] == tableauGrid[j+1].getTable()[i][j+1];
                //End of Game = true when 2 cells are equal, false if not
                if(!endGameProfondeur) { //If 2 cells not equal, break loop
                    //System.out.println("Line " + i + " - Cases " + j + " & " + (j+1) + " not good."); //Test : to REMOVE later
                    break;
                }
            }
            if(endGameProfondeur) { //After a line, if endgame is still true, win detected
                System.out.println("### Win detected on horizontal deep diagonal (left to right) ###");
                displayWinningHorizontalDiagonal3D("l", i);
                return endGameProfondeur;
            }
        }

        //Check on a horizontal deep diagonal from right to left
        for (int i = 0; i < sizeGrid; i++) { //Loop line by line
            for (int j = 0; j < sizeGrid - 1; j++) {
                endGameProfondeur = tableauGrid[j].getTable()[i][sizeGrid-1-j] == tableauGrid[j+1].getTable()[i][sizeGrid-2-j];
                //End of Game = true when 2 cells are equal, false if not
                if(!endGameProfondeur) { //If 2 cells not equal, break loop
                    //System.out.println("Line " + i + " - Cases " + j + " & " + (j+1) + " not good."); //Test : to REMOVE later
                    break;
                }
            }
            if(endGameProfondeur) { //After a line, if endgame is still true, win detected
                System.out.println("### Win detected on horizontal deep diagonal (right to left) ###");
                displayWinningHorizontalDiagonal3D("r", i);
                return endGameProfondeur;
            }
        }

        //Check on a diagonal deep diagonal from left-top-front corner to right-bottom-back corner
        for (int i = 0; i < sizeGrid-1; i++) { //Loop line by line
            endGameProfondeur = tableauGrid[i].getTable()[i][i] == tableauGrid[i+1].getTable()[i+1][i+1];
                //End of Game = true when 2 cells are equal, false if not
                if(!endGameProfondeur) { //If 2 cells not equal, break loop
                    //System.out.println("Line " + i + " - Cases " + j + " & " + (j+1) + " not good."); //Test : to REMOVE later
                    break;
                }
            }
        if(endGameProfondeur) { //After a line, if endgame is still true, win detected
            System.out.println("### Win detected on diagonal deep diagonal (left-top-front corner to right-bottom-back corner) ###");
            displayWinningBasicDiagonal3D("ltf");
            return endGameProfondeur;
        }

        //Check on a diagonal deep diagonal from left-bottom-top corner to right-top-back corner
        for (int i = 0; i < sizeGrid-1; i++) { //Loop line by line
            endGameProfondeur = tableauGrid[i].getTable()[sizeGrid-1-i][i] == tableauGrid[i+1].getTable()[sizeGrid-2-i][i+1];
            //End of Game = true when 2 cells are equal, false if not
            if(!endGameProfondeur) { //If 2 cells not equal, break loop
                //System.out.println("Line " + i + " - Cases " + j + " & " + (j+1) + " not good."); //Test : to REMOVE later
                break;
            }
        }
        if(endGameProfondeur) { //After a line, if endgame is still true, win detected
            System.out.println("### Win detected on diagonal deep diagonal (left-bottom-front corner to right-top-back corner) ###");
            displayWinningBasicDiagonal3D("lbf");
            return endGameProfondeur;
        }

        //Check on a diagonal deep diagonal from right-top-front corner to left-bottom-back corner
        for (int i = 0; i < sizeGrid-1; i++) { //Loop line by line
            endGameProfondeur = tableauGrid[i].getTable()[i][sizeGrid-1-i] == tableauGrid[i+1].getTable()[i+1][sizeGrid-2-i];
            //End of Game = true when 2 cells are equal, false if not
            if(!endGameProfondeur) { //If 2 cells not equal, break loop
                //System.out.println("Line " + i + " - Cases " + j + " & " + (j+1) + " not good."); //Test : to REMOVE later
                break;
            }
        }
        if(endGameProfondeur) { //After a line, if endgame is still true, win detected
            System.out.println("### Win detected on diagonal deep diagonal (right-top-front corner to left-bottom-back corner) ###");
            displayWinningBasicDiagonal3D("rtf");
            return endGameProfondeur;
        }

        //Check on a diagonal deep diagonal from right-bottom-front corner to left-top-back corner
        for (int i = 0; i < sizeGrid-1; i++) { //Loop line by line
            endGameProfondeur = tableauGrid[i].getTable()[sizeGrid-1-i][sizeGrid-1-i] == tableauGrid[i+1].getTable()[sizeGrid-2-i][sizeGrid-2-i];
            //End of Game = true when 2 cells are equal, false if not
            if(!endGameProfondeur) { //If 2 cells not equal, break loop
                //System.out.println("Line " + i + " - Cases " + j + " & " + (j+1) + " not good."); //Test : to REMOVE later
                break;
            }
        }
        if(endGameProfondeur) { //After a line, if endgame is still true, win detected
            System.out.println("### Win detected on diagonal deep diagonal (right-bottom-front corner to left-top-back corner) ###");
            displayWinningBasicDiagonal3D("rbf");
            return endGameProfondeur;
        }


        return endGameProfondeur;
    }
}
