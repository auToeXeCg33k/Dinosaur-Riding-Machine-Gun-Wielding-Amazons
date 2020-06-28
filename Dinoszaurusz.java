public class Dinoszaurusz implements Entity {
  private String nev;
  
  private double elet;
  
  private boolean alive;
  
  private boolean tamed;
  
  public Dinoszaurusz(String nev) {
    this.nev = nev;
    this.alive = true;
    this.elet = 150.0D;
  }
  
  public String getNev() {
    return this.nev;
  }
  
  public boolean isAlive() {
    return this.alive;
  }
  
  public void setTamed(boolean b) {
    this.tamed = b;
  }
  
  public boolean getTamed() {
    return this.tamed;
  }
  
  public String toString() {
    return this.nev;
  }
  
  public void decHP(double r) {
    if (this.elet - r >= 0.0D) {
      this.elet -= r;
    } else {
      this.elet = 0.0D;
      this.alive = false;
    } 
  }
  
  public void incHP(double r) {
    if (this.elet + r <= 150.0D) {
      this.elet += r;
    } else {
      this.elet = 150.0D;
    } 
    this.alive = true;
  }
  
  public double getHP() {
    return this.elet;
  }
}
