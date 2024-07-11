package Players;
import Grid.Grid;

import java.awt.event.MouseEvent;

public class HumanPlayer extends Player{

    public HumanPlayer(COLOR_ENUM _color){
        super(_color);
    }

    @Override
    public int do_turn(Grid tableau) {
        Boolean turnCompleted = false;
        return 0;
    }

    public void evaluationFunction(Grid tableau) {
        int plateauLength = tableau.getLength();
        for(int i = 0; i < plateauLength; i++){
            int countCol = 0;
            if (tableau.canAddToken(i)){
                countCol += evaluateColumn(tableau, i);
            }
        }
    }

    public int evaluateColumn(Grid tableau, int column){
        int scoreOfYourColor = tableau.calculateScoreOfColorOnColumn(column, this.getColor());
        int scoreOfOpponentColor = tableau.calculateScoreOfColorOnColumn(column, this.getColor() == COLOR_ENUM.RED ? COLOR_ENUM.YELLOW : COLOR_ENUM.RED);
        return scoreOfYourColor - scoreOfOpponentColor;
    }

}
