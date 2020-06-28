package items;

import java.util.Random;

public abstract class GepFegyver implements Item {
  double minDMG;
  
  double maxDMG;
  
  int rate;
  
  public double getDMG() {
    Random rand = new Random();
    double dmg = 0.0D;
    for (int i = 0; i < this.rate; i++)
      dmg += (this.maxDMG - this.minDMG) * rand.nextDouble() + this.minDMG; 
    return dmg;
  }
}
