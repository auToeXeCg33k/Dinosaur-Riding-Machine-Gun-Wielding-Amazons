public class DinoszauruszonLovagloGepfegyveresAmazon {
  private String nev;
  
  private boolean gepfegyver;
  
  private boolean dinoszaurusz;
  
  private boolean lovagol;
  
  private double elet;
  
  private boolean alive;
  
  public DinoszauruszonLovagloGepfegyveresAmazon(String nev, boolean fegyo, boolean dino, boolean lovagol) {
    this.nev = nev;
    this.gepfegyver = fegyo;
    if (lovagol) {
      this.dinoszaurusz = lovagol;
      this.lovagol = lovagol;
    } else {
      this.dinoszaurusz = dino;
      this.lovagol = lovagol;
    } 
    this.elet = 100.0D;
    this.alive = true;
  }
  
  public String getNev() {
    return this.nev;
  }
  
  public void incHP(double n) {
    if (this.elet + n <= 100.0D) {
      this.elet += n;
    } else {
      this.elet = 100.0D;
    } 
    this.alive = true;
  }
  
  public void decHP(double n) {
    if (this.elet - n >= 0.0D) {
      this.elet -= n;
    } else {
      this.elet = 0.0D;
      this.alive = false;
      setDino(false);
    } 
  }
  
  public double getHP() {
    return this.elet;
  }
  
  public double getDMG() {
    double temp = StrictMath.random();
    return temp * 20.0D + 5.0D;
  }
  
  public boolean hasDino() {
    return this.dinoszaurusz;
  }
  
  public void setDino(boolean ertek) {
    if (this.alive)
      if (!ertek) {
        this.dinoszaurusz = ertek;
        this.lovagol = ertek;
      } else {
        this.dinoszaurusz = ertek;
      }  
  }
  
  public boolean isLovagol() {
    return this.lovagol;
  }
  
  public void setLovagol(boolean ertek) {
    if (this.dinoszaurusz)
      this.lovagol = ertek; 
  }
  
  public void leszall() {
    this.lovagol = false;
    System.out.println("Leszalltam a dinoszauruszról xd");
  }
  
  public void felszall() {
    if (this.dinoszaurusz = true)
      this.lovagol = true; 
  }
  
  public void tamad(DinoszauruszonLovagloGepfegyveresAmazon enemy) {
    if (!this.nev.equals(enemy.getNev())) {
      if (this.alive) {
        System.out.print(this.nev + " támad. ");
        if (!this.gepfegyver) {
          System.out.println("Nem tok durrogtatni, nincs gépfegyverem xd");
        } else if (enemy.isLovagol()) {
          enemy.setDino(false);
          System.out.println(enemy.nev + " dínója meghótt.");
        } else {
          double temp = getDMG();
          enemy.decHP(temp);
          System.out.println(enemy.nev + " élete " + enemy.nev + " ponttal csökkent. A megmaradt élete: " + temp);
        } 
      } else {
        System.out.println("nem is élek geci");
      } 
    } else {
      System.out.println("há most lőjem magam gec?");
    } 
  }
}
