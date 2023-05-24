package ProjetAPO;

public class Main {
    public static void main(String[] args) {
       /* Grid grid = new Grid(5);
        grid.displayGrid();
        while(!grid.checkForWinner()){ //If endGame = false, keep playing
            grid.pickNumber(1);
            if(grid.checkForWinner()) //needed to stop game when player 1 wins
                break;
            grid.pickNumber(2);
        }*/
        Grid3D jeu = new Grid3D(3);
        while(!jeu.checkForWinner3D()) {
            jeu.pickNumber3D(1);
            if(jeu.checkForWinner3D()) //needed to stop game when player 1 wins
                break;
            jeu.pickNumber3D(2);
        }
    }

}
