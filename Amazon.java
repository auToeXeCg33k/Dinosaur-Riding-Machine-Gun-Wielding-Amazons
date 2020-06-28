import java.util.HashMap;
import java.util.Map;

public class Amazon implements Entity {
  private String nev;
  
  private boolean alive;
  
  private double elet;
  
  private Dinoszaurusz dinoszaurusz;
  
  private boolean lovagol;
  
  private HashMap<Class<?>, Item[]> inventory;
  
  private GepFegyver gepFegyver;
  
  public Amazon(String nev) {
    this.nev = nev;
    this.dinoszaurusz = null;
    this.lovagol = false;
    this.elet = 100.0D;
    this.alive = true;
    this.inventory = (HashMap)new HashMap<>();
    this.inventory.put(GepFegyver.class, new GepFegyver[2]);
  }
  
  public String getNev() {
    return this.nev;
  }
  
  public double getHP() {
    return this.elet;
  }
  
  public GepFegyver getGepFegyver() {
    return this.gepFegyver;
  }
  
  public Dinoszaurusz getDinoszaurusz() {
    return this.dinoszaurusz;
  }
  
  public boolean isLovagol() {
    return this.lovagol;
  }
  
  public HashMap<Class<?>, Item[]> getInventory() {
    return this.inventory;
  }
  
  public void setLovagol(boolean b) {
    this.lovagol = b;
  }
  
  public boolean putInInventory(Item i) {
    for (Map.Entry<Class<?>, Item[]> entry : this.inventory.entrySet()) {
      if (((Class)entry.getKey()).isInstance(i)) {
        for (int j = 0; j < ((Item[])entry.getValue()).length; j++) {
          if (((Item[])entry.getValue())[j] == null) {
            ((Item[])entry.getValue())[j] = i;
            return true;
          } 
        } 
        return false;
      } 
    } 
    return false;
  }
  
  public Item dropFromInventory(Class<?> c) {
    for (Map.Entry<Class<?>, Item[]> entry : this.inventory.entrySet()) {
      if (((Class)entry.getKey()).isAssignableFrom(c)) {
        for (int j = 0; j < ((Item[])entry.getValue()).length; j++) {
          if (c.equals(((Item[])entry.getValue())[j].getClass())) {
            Item temp = ((Item[])entry.getValue())[j];
            ((Item[])entry.getValue())[j] = null;
            return temp;
          } 
        } 
        return null;
      } 
    } 
    return null;
  }
  
  public boolean equip(Class<?> c) {
    for (int i = 0; i < ((Item[])this.inventory.get(GepFegyver.class)).length; i++) {
      if (c.isInstance(((Item[])this.inventory.get(GepFegyver.class))[i])) {
        this.gepFegyver = (GepFegyver)((Item[])this.inventory.get(GepFegyver.class))[i];
        return true;
      } 
    } 
    return false;
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
  
  public void tame(Dinoszaurusz d) {
    if (this.alive) {
      if (!d.getTamed()) {
        this.dinoszaurusz = d;
        d.setTamed(true);
        System.out.println("a dínó beidomítva");
      } else {
        System.out.println("ez a dínó mán másé");
      } 
    } else {
      System.out.println("nem is élek geci");
    } 
  }
  
  public void tamad(Amazon enemy) {
    if (this.alive) {
      if (!this.nev.equals(enemy.getNev())) {
        if (enemy.alive) {
          if (this.gepFegyver == null) {
            System.out.println("nem is tok durrogtatni, nincs is gépfegyverem");
          } else {
            double temp = this.gepFegyver.getDMG();
            if (enemy.isLovagol()) {
              enemy.getDinoszaurusz().decHP(temp);
              if (enemy.getDinoszaurusz().isAlive()) {
                System.out.println(enemy.nev + " dinoszauruszának élete " + enemy.nev + " ponttal csökkent. A megmaradt élete: " + Math.round(temp));
              } else {
                enemy.setLovagol(false);
                System.out.println(enemy.nev + " dinoszaurusza meghalt.");
              } 
            } else {
              enemy.decHP(temp);
              if (enemy.alive) {
                System.out.println(enemy.nev + " élete " + enemy.nev + " ponttal csökkent. A megmaradt élete: " + Math.round(temp));
              } else {
                System.out.println(enemy.nev + " meghótt a gecibe.");
              } 
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
}
