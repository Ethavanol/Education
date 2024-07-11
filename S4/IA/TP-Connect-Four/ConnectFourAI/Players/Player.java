package Players;

import Grid.Grid;

import java.util.ArrayList;
import java.util.List;

public abstract class Player {

    protected int nodesVisited;
    protected COLOR_ENUM color;
    public Player(COLOR_ENUM _color){
        this.color = _color;
        nodesVisited = 0;
    }

    public int do_turn(Grid tableau){
        return 0;
    };

    public COLOR_ENUM getColor(){
        return this.color;
    }


    //Première fonction d'évaluation. On évalue seulement pour les cases possibles.
    public int[] evaluateBoardForPossiblesCells(Grid tab) {
        int score = 0;
        List<Integer> validMoves = tab.getValidMoves();
        for (int move : validMoves) {
            score += evaluateOnlyPossibleCell(tab, move);
        }
        return new int[]{score};
    }

    public int evaluateOnlyPossibleCell(Grid tableau, int column){
        if(column == -1){
            return 0;
        }
        COLOR_ENUM myColor = this.color;
        COLOR_ENUM opponentColor = this.getColor() == COLOR_ENUM.RED ? COLOR_ENUM.YELLOW : COLOR_ENUM.RED;
        int score = 0;
        score += evaluateCellForColor(tableau, column, myColor);
        score -= evaluateCellForColor(tableau, column, opponentColor);
        return score;
    }

    public int evaluateCellForColor(Grid tableau, int column, COLOR_ENUM color){
        int score = 0;
        score += tableau.calculateScoreOfColorOnLine(column, color);
        score += tableau.calculateScoreOfColorOnColumn(column, color);
        score += tableau.calculateScoreOfColorOnDiagonals(column, color);
        return score;
    }

    //Deuxième fonction d'évaluation. On évalue toutes les cases à chaque tour
    public static int[] evaluateBoard(Grid _grid) {
        int scoreYellow = 0;
        int scoreRed = 0;
        COLOR_ENUM[][] board = _grid.getPlateau();
        int boardWidth = board[0].length;
        int boardLength = board.length;

        for (int row = 0; row < boardLength; row++) {
            for (int col = 0; col < 4; col++) {
                COLOR_ENUM[] line = new COLOR_ENUM[4];
                System.arraycopy(board[row], col, line, 0, 4);
                scoreYellow += evaluateLine(line, COLOR_ENUM.YELLOW);
                scoreRed += evaluateLine(line, COLOR_ENUM.RED);
            }
        }

        for (int col = 0; col < boardWidth; col++) {
            for (int row = 0; row < 3; row++) {
                COLOR_ENUM[] line = new COLOR_ENUM[4];
                for (int i = 0; i < 4; i++) {
                    line[i] = board[row + i][col];
                }
                scoreYellow += evaluateLine(line, COLOR_ENUM.YELLOW);
                scoreRed += evaluateLine(line, COLOR_ENUM.RED);
            }
        }

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 4; col++) {
                COLOR_ENUM[] line = new COLOR_ENUM[4];
                for (int i = 0; i < 4; i++) {
                    line[i] = board[row + i][col + i];
                }
                scoreYellow += evaluateLine(line, COLOR_ENUM.YELLOW);
                scoreRed += evaluateLine(line, COLOR_ENUM.RED);
            }
        }

        for (int row = 3; row < boardLength; row++) {
            for (int col = 0; col < 4; col++) {
                COLOR_ENUM[] line = new COLOR_ENUM[4];
                for (int i = 0; i < 4; i++) {
                    line[i] = board[row - i][col + i];
                }
                scoreYellow += evaluateLine(line, COLOR_ENUM.YELLOW);
                scoreRed += evaluateLine(line, COLOR_ENUM.RED);
            }
        }

        return new int[]{scoreYellow - scoreRed, scoreYellow, scoreRed};
    }

    private static int evaluateLine(COLOR_ENUM[] line, COLOR_ENUM player) {
        int score = 0;
        int emptyCount = 0;
        int playerCount = 0;

        for (COLOR_ENUM cell : line) {
            if (cell == null) {
                emptyCount++;
            } else if (cell == player) {
                playerCount++;
            }
        }

        if (playerCount == 4) {
            score += 1000;
        } else if (playerCount == 3 && emptyCount == 1) {
            score += 50;
        } else if (playerCount == 2 && emptyCount == 2) {
            score += 5;
        } else if (playerCount == 1 && emptyCount == 3) {
            score += 1;
        }

        return score;
    }

    public int getNodesVisited(){
        return nodesVisited;
    }
}
