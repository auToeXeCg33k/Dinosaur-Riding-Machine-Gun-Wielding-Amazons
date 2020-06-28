public class Amazon implements Entity {
  private String nev;
  
  private boolean gepfegyver;
  
  private Dinoszaurusz dinoszaurusz;
  
  private boolean lovagol;
  
  private double elet;
  
  private boolean alive;
  
  public Amazon(String nev) {
    this.nev = nev;
    this.gepfegyver = true;
    this.dinoszaurusz = null;
    this.lovagol = false;
    this.elet = 100.0D;
    this.alive = true;
  }
  
  public String getNev() {
    return this.nev;
  }
  
  public void incHP(double r) {
    if (this.elet + r <= 100.0D) {
      this.elet += r;
    } else {
      this.elet = 100.0D;
    } 
    this.alive = true;
  }
  
  public void decHP(double r) {
    if (this.elet - r >= 0.0D) {
      this.elet -= r;
    } else {
      this.elet = 0.0D;
      this.alive = false;
    } 
  }
  
  public double getHP() {
    return this.elet;
  }
  
  public double getDMG() {
    return 2.0D * (StrictMath.random() * 20.0D + 5.0D);
  }
  
  public void tame(Dinoszaurusz d) {
    if (this.alive) {
      if (this.dinoszaurusz == null) {
        if (!d.getTamed()) {
          this.dinoszaurusz = d;
          d.setTamed(true);
          System.out.println("a dínó beidomítva");
        } else {
          System.out.println("ez a dínó mán másé");
        } 
      } else {
        System.out.println("mán van dínóm");
      } 
    } else {
      System.out.println("nem is élek geci");
    } 
  }
  
  public boolean isLovagol() {
    return this.lovagol;
  }
  
  public void setLovagol(boolean b) {
    this.lovagol = b;
  }
  
  public Dinoszaurusz getDinoszaurusz() {
    return this.dinoszaurusz;
  }
  
  public void tamad(Amazon enemy) {
    if (this.alive) {
      if (!this.nev.equals(enemy.getNev())) {
        if (enemy.alive) {
          if (!this.gepfegyver) {
            System.out.println("nem is tok durrogtatni, nincs is gépfegyverem");
          } else if (enemy.isLovagol()) {
            double temp = getDMG();
            enemy.getDinoszaurusz().decHP(temp);
            if (enemy.getDinoszaurusz().isAlive()) {
              System.out.println(enemy.nev + " dinoszauruszának élete " + enemy.nev + " ponttal csökkent. A megmaradt élete: " + Math.round(temp));
            } else {
              enemy.setLovagol(false);
              System.out.println(enemy.nev + " dinoszaurusza meghalt.");
            } 
          } else {
            double temp = getDMG();
            enemy.decHP(temp);
            if (enemy.alive) {
              System.out.println(enemy.nev + " élete " + enemy.nev + " ponttal csökkent. A megmaradt élete: " + Math.round(temp));
            } else {
              System.out.println(enemy.nev + " meghótt a gecibe.");
            } 
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
  
  public boolean getGepfegyver() {
    return this.gepfegyver;
  }
}
