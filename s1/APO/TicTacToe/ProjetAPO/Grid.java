package ProjetAPO;

import java.util.Scanner;

public class Grid {
    private int sizeN;
    private String [][] table;

    private int turn;
    private boolean endGame;

    public Grid() { //Default : size = 3
        this.sizeN = 3;
        this.endGame = false;
        this.table = new String[sizeN][sizeN];

        int counter = 1;
        for (int i = 0; i < sizeN; i++) {
            for (int j = 0; j < sizeN; j++) {
                table[i][j] = String.valueOf(counter);
                counter ++;
            }
        }
    }

    public Grid(int sizeM) {
        this.sizeN = sizeM;
        this.endGame = false;
        this.table = new String[sizeN][sizeN];

        int counter = 1;
        for (int i = 0; i < sizeN; i++) {
            for (int j = 0; j < sizeN; j++) {
                table[i][j] = String.valueOf(counter);
                counter++;
            }
        }
    }

    public int getSizeN() {
        return sizeN;
    }

    public void setSizeX(int sizeN) {
        this.sizeN = sizeN;
    }

    public String[][] getTable() {
        return table;
    }

    public boolean getEndGame() {
        return endGame;
    }

    public void displayGrid(){
        for (int i = 0; i < table.length; i++) {
            System.out.print("| ");
            for (int j = 0; j < table[i].length; j++) {
                System.out.print(table[i][j]);
                if (j !=table[i].length-1) System.out.print("  ");
            }
            System.out.print(" |");
            System.out.println();
        }
    }
    public boolean verifyEntry(String number,int player){
        String grid2[][] = this.table;
        for (int i = 0; i < grid2.length; i++) {
            System.out.print("|");
            for (int j = 0; j < grid2[i].length; j++) {
                if (grid2[i][j].equals(number)) {
                    if(player == 1){
                        System.out.print(">x<");
                    }else{
                        System.out.print(">o<");
                    }

                }
                else{
                    System.out.print(" " + table[i][j] + " ");
            }
            }
            System.out.print("|");
            System.out.println();
        }
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

    public static boolean isNumeric(String str) {
        try {
            Double.parseDouble(str);
            return true;
        } catch(NumberFormatException e){
            return false;
        }
    }

    public void pickNumber(int player) {
        char isANumber;
        double numberPicked;
        int nbMax = sizeN * sizeN;
        Scanner scanner = new Scanner(System.in);
        String number;
        while (true) {
            System.out.print("Pick a number from 1 to "+ nbMax +": ");
            number = scanner.next();

            if(isNumeric(number)){
                numberPicked = Double.parseDouble(number);
                if(numberPicked >0 && numberPicked <= nbMax){
                    break;
                }
                else {
                    System.out.println("This index is out of range");
                }
            } else {
                System.out.println("Invalid input.");
            }

        }


        boolean check = false;
        boolean verify = false;
        for (int i = 0; i < table.length; i++) {
            for (int j = 0; j < table[i].length; j++) {
                if (table[i][j].equals(number)) {
                    check = true;
                    if (player == 1) {
                         verify = verifyEntry(number,player);
                        if(verify){
                        table[i][j] = "X";
                        }
                    } else {
                        verify = verifyEntry(number,player);
                        if(verify){
                            table[i][j] = "O";
                        }
                    }
                }
            }
        }
        if (!check) {
            System.out.println("Already filled ! Try again");
            pickNumber(player);
        } else if (!verify) {
            displayGrid();
            pickNumber(player);
        } else
        {
            displayGrid();
        }
        turn ++;
    }
    public void displayWinningLine(String pos, int line){
        String player;
        if(turn % 2 == 0) {
            player = "O";
        }else{;
            player = "X";
        }
        if (pos.equals("c")) { // If it is on a column
            switch(line){
                case 1:
                    for(int i =0; i<sizeN; i++) {
                        table[i][0] = "[" + player + "]";
                    }
                    displayGrid();
                    break;
                case 2:
                    for(int i =0; i<sizeN; i++) {
                        table[i][1] = "[" + player + "]";
                    }
                    displayGrid();
                    break;
                case 3:
                    for(int i =0; i<sizeN; i++) {
                        table[i][2] = "[" + player + "]";
                    }
                    displayGrid();
                    break;
            }
        } else if (pos.equals("l")) {
            switch(line){
                case 1:
                    for(int i =0; i<sizeN; i++) {
                        table[0][i] = "[" + player + "]";
                    }
                    displayGrid();
                    break;
                case 2:
                    for(int i =0; i<sizeN; i++) {
                        table[1][i] = "[" + player + "]";
                    }
                    displayGrid();
                    break;
                case 3:
                    for(int i =0; i<sizeN; i++) {
                        table[2][i] = "[" + player + "]";
                    }
                    displayGrid();
                    break;
            }
        }else if (pos.equals("d1")) {
            for(int i =0; i<sizeN; i++) {
                table[i][i] = "[" + player + "]";
            }
            displayGrid();
        }else if (pos.equals("d2")) {
            for(int i =0; i<sizeN; i++) {
                table[i][sizeN - 1 - i] = "[" + player + "]";
            }
            displayGrid();
        }
    }
    public boolean checkForWinner() {

        for (int i = 0; i < sizeN; i++) { //Loop line by line
            for (int j = 0; j < sizeN-1; j++) {
                endGame = table[i][j] == table[i][j+1];//End of Game = true when 2 cells are equal, false if not
                if(!endGame) { //If 2 cells not equal, break loop
                    break;
                }
            }
            if(endGame) { //After a line, if endgame is still true, win detected
                i = i+1;
                System.out.println("### Win detected on line " + i + " ###");
                displayWinningLine("l",i);
                return endGame;
            }
        }
        /////////////////////////////////////////////////////////////
        for (int j = 0; j < sizeN; j++) { //Loop column by column
            for (int i = 0; i < sizeN - 1; i++) {
                endGame = table[i][j] == table[i+1][j];//End of Game = true when 2 cells are equal, false if not
                if(!endGame) { //If 2 cells not equal, break loop
                    break;
                }
            }
            if(endGame) { //After a column, if endgame is still true, win detected
                j = j+1;
                System.out.println("### Win detected on column " + j + " ###");
                displayWinningLine("c",j);
                return endGame;
            }
        }
        /////////////////////////////////////////////////////////////
        for (int i = 0; i < sizeN-1; i++) { //Loop diagonal 1 (\)
            endGame = table[i][i] == table[i+1][i+1]; //End of Game = true when 2 cells are equal, false if not
            if(!endGame) { //If 2 cells not equal, break loop
                break;
            }
        }
        if(endGame) { //After diagonal, if endgame is still true, win detected
            System.out.println("### Win detected on diagonal \\ ###");
            displayWinningLine("d1",0);
            return endGame;
        }

        /////////////////////////////////////////////////////////////
        for (int i = 0; i < sizeN-1; i++) { //Loop diagonal 2 (/)
            endGame = table[i][table.length-1-i] == table[i+1][table.length-1-i -1]; //End of Game = true when 2 cells are equal, false if not
            if(!endGame) { //If 2 cells not equal, break loop
                break;
            }
        }
        if(endGame) { //After diagonal, if endgame is still true, win detected
            System.out.println("### Win detected on diagonal / ###");
            displayWinningLine("d2",0);
            return endGame;
        }

        return endGame; //This return means no win this round
    }

}
