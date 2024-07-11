package Tree;

import Grid.Grid;
import Players.COLOR_ENUM;

import java.util.ArrayList;
import java.util.List;

public class Node {
    public Grid board;
    public COLOR_ENUM player;
    public Node parent;
    public List<Node> children;
    public int wins;
    public int visits;
    public List<Integer> untriedMoves;
    public int depth;
    public Integer move; // Added to store the move leading to this node

    public Node(Grid board, COLOR_ENUM player, Node parent, Integer move) {
        this.board = board;
        this.player = player;
        this.parent = parent;
        this.children = new ArrayList<>();
        this.wins = 0;
        this.visits = 0;
        this.untriedMoves = board.getValidMoves();
        this.depth = (parent == null) ? 0 : parent.depth + 1;
        this.move = move;
    }

    public int getMaxDepth() {
        if (this.children.isEmpty()) {
            return this.depth;
        }

        int maxDepth = this.depth;
        for (Node child : this.children) {
            maxDepth = Math.max(maxDepth, child.getMaxDepth());
        }
        return maxDepth;
    }
}
