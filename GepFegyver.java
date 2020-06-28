import java.util.Random;

public abstract class GepFegyver implements Item {
  double minDMG;
  
  double maxDMG;
  
  int rate;
  
  private boolean held;
  
  public double getDMG() {
    Random rand = new Random();
    double dmg = 0.0D;
    for (int i = 0; i < this.rate; i++)
      dmg += (this.maxDMG - this.minDMG) * rand.nextDouble() + this.minDMG; 
    return dmg;
  }
  
  public double getRate() {
    return this.rate;
  }
  
  public boolean isHeld() {
    return this.held;
  }
}
