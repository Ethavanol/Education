import Players.*;
import Game.Game;
import Grid.Grid;
import Players.MonteCarloPlayer;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Puissance4 {
    private JFrame fenetre;
    private JPanel plateauPanel;
    private JPanel controlsPanel;
    private JPanel emptyPanel;
    private JComboBox<String> player1ComboBox;
    private JComboBox<String> player2ComboBox;
    private JTextField delayField;
    private MouseListener mouseListener;

    private Boolean mouseListenerEnabled;
    private Boolean hasPlayed;
    private int delay;

    private Player player1;
    private Player player2;

    private Player actual_player;
    private Grid grid;

    public Puissance4() {
        grid = new Grid();
        player1 = new HumanPlayer(COLOR_ENUM.YELLOW);
        player2 = new AlphaBetaIAPlayer(COLOR_ENUM.RED);
        actual_player = player1;
        hasPlayed = false;
        fenetre = new JFrame("Puissance 4");
        delay = 0;
        plateauPanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                for (int i = 0; i < grid.getLength(); i++) {
                    for (int j = 0; j < grid.getWidth(); j++) {
                        g.setColor(getColor(grid.getCell(i,j)));
                        g.fillOval(j * 50 + 25, i * 50 + 25, 25, 25);
                        g.setColor(Color.BLACK);
                        g.drawOval(j * 50 + 25, i * 50 + 25, 25, 25);
                    }
                }
            }

            private Color getColor(COLOR_ENUM c) {
                if (c == null) {
                    return Color.WHITE;
                } else {
                    switch (c) {
                        case YELLOW:
                            return Color.YELLOW;
                        case RED:
                            return Color.RED;
                        default:
                            return Color.WHITE;
                    }
                }
            }
        };
        plateauPanel.setPreferredSize(new Dimension(380, 350));

        controlsPanel = new JPanel(new GridLayout(2, 3)); // Utilisation d'un GridLayout pour les étiquettes et les listes déroulantes
        JLabel label1 = new JLabel("Player 1:");
        JLabel label2 = new JLabel("Player 2:");
        JLabel delayLabel = new JLabel("Délai (ms):"); // Étiquette pour le délai
        String[] players = {"Humain", "IA minimax", "IA alphabeta", "IA MCTS"}; // Exemple de noms de joueurs
        player1ComboBox = new JComboBox<>(players);
        player2ComboBox = new JComboBox<>(players);
        delayField = new JTextField(String.valueOf(delay));

        player1ComboBox.setSelectedIndex(0); // Humain par défaut pour player1
        player2ComboBox.setSelectedIndex(2); // Minimax par défaut pour player2

        player1ComboBox.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String selectedPlayer = (String) player1ComboBox.getSelectedItem();
                switch (selectedPlayer) {
                    case "Humain":
                        setPlayer1(new HumanPlayer(player1.getColor()));
                        break;
                    case "IA minimax":
                        setPlayer1(new MinimaxIAPlayer(player1.getColor()));
                        break;
                    case "IA alphabeta":
                        setPlayer1(new AlphaBetaIAPlayer(player1.getColor()));
                        break;
                    case "IA MCTS":
                        setPlayer1(new MonteCarloPlayer(player1.getColor()));
                        break;
                }
                if(actual_player.getColor() == player1.getColor()){
                    setActual_player(player1);
                }
            }
        });

        player2ComboBox.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String selectedPlayer = (String) player2ComboBox.getSelectedItem();
                switch (selectedPlayer) {
                    case "Humain":
                        setPlayer2(new HumanPlayer(player2.getColor()));
                        break;
                    case "IA minimax":
                        setPlayer2(new MinimaxIAPlayer(player2.getColor()));
                        break;
                    case "IA alphabeta":
                        setPlayer2(new AlphaBetaIAPlayer(player2.getColor()));
                        break;
                    case "IA MCTS":
                        setPlayer2(new MonteCarloPlayer(player2.getColor()));
                        break;
                }
                if(actual_player.getColor() == player2.getColor()){
                    setActual_player(player2);
                }
            }
        });

        delayField.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    int newDelay = Integer.parseInt(delayField.getText());
                    if (newDelay < 0) {
                        JOptionPane.showMessageDialog(fenetre, "Le délai ne peut pas être négatif.");
                        delayField.setText(String.valueOf(delay)); // Rétablir la valeur précédente
                    } else {
                        delay = newDelay; // Mettre à jour la valeur du délai
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(fenetre, "Veuillez entrer un nombre valide pour le délai.");
                    delayField.setText(String.valueOf(delay)); // Rétablir la valeur précédente
                }
            }
        });

        // Ajout des étiquettes et des listes déroulantes au panneau de contrôles
        controlsPanel.add(label1);
        controlsPanel.add(label2);
        controlsPanel.add(delayLabel);
        controlsPanel.add(player1ComboBox);
        controlsPanel.add(player2ComboBox);
        controlsPanel.add(delayField);

        // Ajout des panneaux à la fenêtre
        fenetre.add(controlsPanel, BorderLayout.NORTH);
        fenetre.add(plateauPanel, BorderLayout.CENTER);

        mouseListener = new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (!getMouseListenerEnabled()) {
                    return;
                }
                int colonne = e.getX() / 50;
                if (colonne >= 0 && colonne < grid.getWidth()) {
                    if (!grid.canAddToken(colonne)) {
                        JOptionPane.showMessageDialog(fenetre, "Cette colonne est déjà pleine!");
                        return;
                    } else {
                        COLOR_ENUM color = actual_player.getColor();
                        grid.addToken(colonne, color);
                        setMouseListenerEnabled(false);
                        setHasPlayed(true);
                    }
                }
            }
        };
        plateauPanel.addMouseListener(mouseListener);

        fenetre.pack();
        fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        fenetre.setVisible(true);
        startGame();
    }

    public void startGame() {
        int MCDepthSum = 0;
        int nbOfTurns = 0;
        while(!this.grid.gridFull() && !this.grid.checkWin()) {
            setHasPlayed(false);
            while (!getHasPlayed()) {
                if (this.actual_player instanceof HumanPlayer) {
                    setMouseListenerEnabled(true);
                } else {
                    setMouseListenerEnabled(false);
                    try {
                        Thread.sleep(delay);
                    } catch (InterruptedException ex) {
                        Thread.currentThread().interrupt(); // Restaure l'état d'interruption
                    }
                    if(actual_player instanceof MonteCarloPlayer){
                        MCDepthSum += ((MonteCarloPlayer) actual_player).getMaxDepth();
                        nbOfTurns++;
                    }
                    this.grid.addToken(this.actual_player.do_turn(this.grid), this.actual_player.getColor());
                    setHasPlayed(true);
                }
            }
            plateauPanel.repaint();
            if (grid.checkWin()){
                JOptionPane.showMessageDialog(fenetre, "Le joueur " + actual_player.getColor() + " a gagné!");
            }
            switchPlayer();
        }

        System.out.println("Player 1 : " + player1ComboBox.getSelectedItem() + " a visité " + player1.getNodesVisited() + " noeuds");
        System.out.println("Player 2 : " + player2ComboBox.getSelectedItem() + " a visité " + player2.getNodesVisited() + " noeuds");
        if(player1 instanceof MonteCarloPlayer){
            double MCDepthAverage = (double) MCDepthSum/nbOfTurns;
            System.out.println("MonteCarlo Player a une moyenne de branche maximale de " + MCDepthAverage);
        }
        if(player2 instanceof MonteCarloPlayer){
            double MCDepthAverage = (double) MCDepthSum/nbOfTurns;
            System.out.println("MonteCarlo Player a une moyenne de branche maximale de " + MCDepthAverage);
        }
        if(this.grid.gridFull()){
            JOptionPane.showMessageDialog(fenetre, "La grille est pleine!");
        }
    }

    public void switchPlayer(){
        if (actual_player == this.player1){
            actual_player = this.player2;
        } else {
            actual_player = this.player1;
        }
    }

    public Boolean getHasPlayed() {
        return hasPlayed;
    }

    public void setHasPlayed(Boolean hasPlayed) {
        this.hasPlayed = hasPlayed;
    }

    public Boolean getMouseListenerEnabled() {
        return mouseListenerEnabled;
    }

    public void setMouseListenerEnabled(Boolean mouseListenerEnabled) {
        this.mouseListenerEnabled = mouseListenerEnabled;
    }

    public void setActual_player(Player actual_player) {
        this.actual_player = actual_player;
    }

    public void setPlayer1(Player player1) {
        this.player1 = player1;
    }

    public void setPlayer2(Player player2) {
        this.player2 = player2;
    }

    public static void main(String[] args) {
        new Puissance4();

    }


}
