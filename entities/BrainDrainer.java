package entities;

import java.util.Random;

public class BrainDrainer {
  private final double minDMG = 60.0D;
  
  private final double maxDMG = 90.0D;
  
  public String attack(Amazon amazon) {
    Random random = new Random();
    double dmg = (this.maxDMG - this.minDMG) * random.nextDouble() + this.minDMG;
    String ret = amazon.getNev().concat(" amazont megbaszta a braindrainer. ");
    if (amazon.isLovagol()) {
      amazon.getDinoszaurusz().decHP(dmg);
      if (amazon.getDinoszaurusz().getHP() > 0.0D)
        return ret.concat("A dinoszauruszának élete " + Math.round(dmg) + " ponttal csökkent. A megmaradt élete: " + Math.round(amazon.getDinoszaurusz().getHP()) + ".\n"); 
      amazon.setLovagol(false);
      return ret.concat(amazon.getNev().concat(" dinoszaurusza megdöglött.\n"));
    } 
    amazon.decHP(dmg);
    if (amazon.getHP() != 0.0D)
      return ret.concat("Az élete " + Math.round(dmg) + " ponttal csökkent. A megmaradt élete: " + Math.round(amazon.getHP()) + ".\n"); 
    return ret.concat("Meghótt a gecibe.\n");
  }
}
