package Game;

import Grid.Grid;
import Players.COLOR_ENUM;
import Players.HumanPlayer;
import Players.Player;

public class Game {

    private Grid plateau;

    private Player player1;
    private Player player2;

    private Player actual_player;

    public Game(Player _player1, Player _player2){
        plateau = new Grid();
        player1 = _player1;
        player2 = _player2;
        actual_player = player1;
    }

    public void addToken(int column) {
        for (int i = plateau.getLength() - 1; i >= 0; i--) {
            if (plateau.getCell(i, column) == null) {
                plateau.setCell(i, column, actual_player.getColor());
                return;
            }
        }
    }

    public void switchPlayer(){
        if (actual_player == player1){
            actual_player = player2;
        } else {
            actual_player = player1;
        }
    }

    public Boolean checkWin(){
        int plateauLength = plateau.getLength();
        int plateauWidth = plateau.getWidth();
        for (int i = 0; i < plateauLength; i++) {
            for (int j = 0; j < plateauWidth - 3; j++) {
                if (plateau.getCell(i, j) != null && plateau.getCell(i, j) == plateau.getCell(i, j + 1) && plateau.getCell(i, j) == plateau.getCell(i,j + 2) && plateau.getCell(i, j) == plateau.getCell(i, j + 3)) {
                    return true;
                }
            }
        }
        for (int i = 0; i < plateau.getLength() - 3; i++) {
            for (int j = 0; j < plateau.getWidth(); j++) {
                if (plateau.getCell(i, j) != null && plateau.getCell(i, j) == plateau.getCell(i + 1, j ) && plateau.getCell(i, j) == plateau.getCell(i + 2,j) && plateau.getCell(i, j) == plateau.getCell(i + 3,j)) {
                    return true;
                }
            }
        }
        for (int i = 0; i < plateau.getLength() - 3; i++) {
            for (int j = 0; j < plateau.getWidth() - 3; j++) {
                if (plateau.getCell(i, j) != null && plateau.getCell(i, j) == plateau.getCell(i + 1, j + 1) && plateau.getCell(i, j) == plateau.getCell(i + 2, j + 2) && plateau.getCell(i, j) == plateau.getCell(i + 3, j + 3)) {
                    return true;
                }
            }
        }
        for (int i = 0; i < plateau.getLength() - 3; i++) {
            for (int j = 3; j < plateau.getWidth(); j++) {
                if (plateau.getCell(i, j) != null && plateau.getCell(i, j) == plateau.getCell(i + 1, j  - 1) && plateau.getCell(i, j) == plateau.getCell(i + 2, j - 2) && plateau.getCell(i, j) == plateau.getCell(i + 3, j - 3)) {
                    return true;
                }
            }
        }
        return false;
    }

    public Grid getPlateau() {
        return plateau;
    }

    public Player getActualPlayer() {
        return actual_player;
    }

    public void setPlayer1(Player player1) {
        this.player1 = player1;
    }

    public void setPlayer2(Player player2) {
        this.player2 = player2;
    }
}
