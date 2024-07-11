package Players;
import Grid.Grid;

import java.util.ArrayList;
import java.util.List;


public class MinimaxIAPlayer extends Player{

    public MinimaxIAPlayer(COLOR_ENUM _color){
        super(_color);
    }

    @Override
    public int do_turn(Grid tableau) {
        return getBestMoveMinimax(tableau, 5, this.color);
    }

    private int[] joueurMax(Grid grid, int depth, COLOR_ENUM player) {
        nodesVisited++;
        List<Integer> validMoves = grid.getValidMoves();
        boolean isTerminal = grid.isTerminal();

        if (depth == 0 || isTerminal) {
            int[] scoreE = evaluateBoard(grid);
            int score = (player == COLOR_ENUM.YELLOW) ? scoreE[0] : -scoreE[0];
            return new int[]{score, -1};
        }

        int value = Integer.MIN_VALUE;
        Integer bestMove = -1;
        for (Integer col : validMoves) {
            Grid newBoard = makeMove(grid, col, player);
            int[] newResult = joueurMin(newBoard, depth - 1, player);
            if (newResult[0] > value) {
                value = newResult[0];
                bestMove = col;
            }
        }
        return new int[]{value, bestMove};
    }

    private int[] joueurMin(Grid grid, int depth, COLOR_ENUM player) {
        nodesVisited++;
        COLOR_ENUM opponent = (player == COLOR_ENUM.YELLOW) ? COLOR_ENUM.RED : COLOR_ENUM.YELLOW;
        List<Integer> validMoves = grid.getValidMoves();
        boolean isTerminal = grid.isTerminal();

        if (depth == 0 || isTerminal) {
            int[] scoreE = evaluateBoard(grid);
            int score = (player == COLOR_ENUM.YELLOW) ? scoreE[0] : -scoreE[0];
            return new int[]{score, -1};
        }

        int value = Integer.MAX_VALUE;
        Integer bestMove = -1;
        for (Integer col : validMoves) {
            Grid newBoard = makeMove(grid, col, opponent);
            int[] newResult = joueurMax(newBoard, depth - 1, player);
            if (newResult[0] < value) {
                value = newResult[0];
                bestMove = col;
            }
        }
        return new int[]{value, bestMove};
    }

    private int[] minimax(Grid grid, int depth, boolean maximizingPlayer, COLOR_ENUM player) {
        if (maximizingPlayer) {
            return joueurMax(grid, depth, player);
        } else {
            return joueurMin(grid, depth, player);
        }
    }

    public Integer getBestMoveMinimax(Grid grid, int depth, COLOR_ENUM player) {
        int[] result = minimax(grid, depth, true, player);
        return result[1];
    }

    private Grid makeMove(Grid grid, int column, COLOR_ENUM player) {
        Grid newGrid = new Grid(grid.getPlateau());
        if(newGrid.canAddToken(column)){
            newGrid.addToken(column, player);
        }
        return newGrid;
    }

}
