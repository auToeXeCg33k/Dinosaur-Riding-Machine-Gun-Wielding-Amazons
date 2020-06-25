public class Amazon implements Entity {
  private String nev;
  
  private boolean gepfegyver;
  
  private boolean dinoszaurusz;
  
  private boolean lovagol;
  
  private double elet;
  
  private boolean alive;
  
  public Amazon(String nev, boolean fegyo, boolean dino, boolean lovagol) {
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
    return StrictMath.random() * 20.0D + 5.0D;
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
  
  public void tamad(Amazon enemy) {
    if (this.alive) {
      if (!this.nev.equals(enemy.getNev())) {
        if (enemy.getHP() != 0.0D) {
          if (!this.gepfegyver) {
            System.out.println("nem is tok durrogtatni, nincs is gépfegyverem");
          } else if (enemy.isLovagol()) {
            enemy.setDino(false);
            System.out.println(enemy.nev + " dínója megdöglött.");
          } else {
            double temp = getDMG();
            enemy.decHP(temp);
            System.out.println(enemy.nev + " élete " + enemy.nev + " ponttal csökkent. A megmaradt élete: " + Math.round(temp));
          } 
        } else {
          System.out.println("nem is él ez a szerencsétlen");
        } 
      } else {
        System.out.println("há most lőjem magam gec?");
      } 
    } else {
      System.out.println("nem is élek geci");
    } 
  }
}
