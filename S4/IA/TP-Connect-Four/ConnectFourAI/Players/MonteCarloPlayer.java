package Players;

import Grid.Grid;
import Tree.Node;

import java.util.List;
import java.util.Random;

public class MonteCarloPlayer extends Player {
    private static final double EXPLORATION_VALUE = Math.sqrt(2);
    private static final int WIN_SCORE = 10;
    private static final int LOSE_SCORE = -10;
    private static final int NEUTRAL_SCORE = 0;
    private int maxDepth;

    public MonteCarloPlayer(COLOR_ENUM _color) {
        super(_color);
    }

    @Override
    public int do_turn(Grid tableau) {
        return getBestMoveMCTS(tableau, this.color, 50000);
    }

    public int getBestMoveMCTS(Grid board, COLOR_ENUM player, int iterations) {
        Node root = createNode(board, player, null, null);
        Node bestChildNode = mcts(root, iterations, EXPLORATION_VALUE);
        this.maxDepth = root.getMaxDepth();
        return bestChildNode.move; // Return the move leading to the best child
    }

    private Node createNode(Grid board, COLOR_ENUM player, Node parent, Integer move) {
        return new Node(board, player, parent, move);
    }

    private Node bestChild(Node node, double explorationValue) {
        double bestValue = Double.NEGATIVE_INFINITY;
        Node bestNode = null;

        for (Node child : node.children) {
            double uctValue = (double) child.wins / (double) child.visits +
                    explorationValue * Math.sqrt(2 * Math.log(node.visits) / (double) child.visits);
            if (uctValue > bestValue) {
                bestValue = uctValue;
                bestNode = child;
            }
        }

        return bestNode;
    }

    private Node mcts(Node root, int iterations, double explorationValue) {
        for (int i = 0; i < iterations; i++) {
            Node node = treePolicy(root, explorationValue);
            int reward = defaultPolicy(node);
            backup(node, reward);
        }
        return bestChild(root, 0); // No exploration in the final decision
    }

    private Node treePolicy(Node node, double explorationValue) {
        while (!isTerminalNode(node.board)) {
            if (!node.untriedMoves.isEmpty()) {
                return expand(node);
            } else {
                node = bestChild(node, explorationValue);
            }
        }
        return node;
    }

    private Node expand(Node node) {
        int move = node.untriedMoves.remove(0);
        Grid newBoard = makeMove(node.board, move, node.player);
        COLOR_ENUM newPlayer = (node.player == COLOR_ENUM.YELLOW) ? COLOR_ENUM.RED : COLOR_ENUM.YELLOW;
        Node childNode = createNode(newBoard, newPlayer, node, move);
        node.children.add(childNode);
        return childNode;
    }

    private int defaultPolicy(Node node) {
        Grid currentBoard = new Grid(node.board.getPlateau());
        COLOR_ENUM currentPlayer = node.player;
        Random random = new Random();

        while (!isTerminalNode(currentBoard)) {
            List<Integer> validMoves = currentBoard.getValidMoves();
            int move = validMoves.get(random.nextInt(validMoves.size()));
            currentBoard = makeMove(currentBoard, move, currentPlayer);
            currentPlayer = (currentPlayer == COLOR_ENUM.YELLOW) ? COLOR_ENUM.RED : COLOR_ENUM.YELLOW;
        }

        int[] scoreE = evaluateBoard(currentBoard);
        int scoreYellow = scoreE[0];
        int scoreRed = -scoreE[0];

        if (scoreYellow >= 1000) {
            return LOSE_SCORE; // Yellow wins
        } else if (scoreRed >= 1000) {
            return WIN_SCORE; // Red wins
        } else {
            return NEUTRAL_SCORE; // Draw or neutral
        }
    }

    private void backup(Node node, int reward) {
        while (node != null) {
            node.visits++;
            if (node.player == COLOR_ENUM.YELLOW) {
                node.wins += reward;
            } else {
                node.wins -= reward;
            }
            node = node.parent;
        }
    }

    private Grid makeMove(Grid grid, int column, COLOR_ENUM player) {
        Grid newGrid = new Grid(grid.getPlateau());
        if (newGrid.canAddToken(column)) {
            newGrid.addToken(column, player);
        }
        return newGrid;
    }

    private boolean isTerminalNode(Grid board) {
        return board.isTerminal();
    }

    public int getMaxDepth() {
        return maxDepth;
    }
}
