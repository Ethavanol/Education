package Players;
import Grid.Grid;

import java.util.List;

public class AlphaBetaIAPlayer extends Player {

    public AlphaBetaIAPlayer(COLOR_ENUM _color){
        super(_color);
    }

    @Override
    public int do_turn(Grid tableau) {
        return getBestMoveAlphaBeta(tableau, 5, Integer.MIN_VALUE, Integer.MAX_VALUE, this.color);
    }

    private int[] joueurMax(Grid grid, int depth, int alpha, int beta, COLOR_ENUM player) {
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
            int[] newResult = joueurMin(newBoard, depth - 1, alpha, beta, player);
            if (newResult[0] > value) {
                value = newResult[0];
                bestMove = col;
            }
            alpha = Math.max(alpha, value);
            if (alpha >= beta) {
                break; // Beta cutoff
            }
        }
        return new int[]{value, bestMove};
    }

    private int[] joueurMin(Grid grid, int depth, int alpha, int beta, COLOR_ENUM player) {
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
            int[] newResult = joueurMax(newBoard, depth - 1, alpha, beta, player);
            if (newResult[0] < value) {
                value = newResult[0];
                bestMove = col;
            }
            beta = Math.min(beta, value);
            if (alpha >= beta) {
                break; // Alpha cutoff
            }
        }
        return new int[]{value, bestMove};
    }

    private int[] alphaBeta(Grid grid, int depth, int alpha, int beta, boolean maximizingPlayer, COLOR_ENUM player) {
        if (maximizingPlayer) {
            return joueurMax(grid, depth, alpha, beta, player);
        } else {
            return joueurMin(grid, depth, alpha, beta, player);
        }
    }

    public Integer getBestMoveAlphaBeta(Grid grid, int depth, int alpha, int beta, COLOR_ENUM player) {
        int[] result = alphaBeta(grid, depth, alpha, beta, true, player);
        return result[1];
    }

    private Grid makeMove(Grid grid, int column, COLOR_ENUM player) {
        Grid newGrid = new Grid(grid.getPlateau());
        if (newGrid.canAddToken(column)) {
            newGrid.addToken(column, player);
        }
        return newGrid;
    }
}
