package entities;

import items.GepFegyver;
import items.Item;
import java.util.HashMap;
import java.util.Map;

public class Amazon implements Entity {
  private String nev;
  
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
      return;
    } 
    this.elet = 100.0D;
  }
  
  public void decHP(double r) {
    if (this.elet - r >= 0.0D) {
      this.elet -= r;
      return;
    } 
    this.elet = 0.0D;
  }
  
  public void tame(Dinoszaurusz d) {
    this.dinoszaurusz = d;
    d.setTamed(true);
  }
  
  public int tamad(Amazon enemy) {
    if (this.gepFegyver == null) {
      System.out.println("Nem tok durrogtatni, fasse fogok.\n");
      return 2;
    } 
    double temp = this.gepFegyver.getDMG();
    if (enemy.isLovagol()) {
      enemy.getDinoszaurusz().decHP(temp);
      if (enemy.getDinoszaurusz().getHP() > 0.0D) {
        System.out.println(enemy.nev + " dinoszauruszának élete " + enemy.nev + " ponttal csökkent. A megmaradt élete: " + Math.round(temp) + ".\n");
        return 0;
      } 
      enemy.setLovagol(false);
      System.out.println(enemy.nev + " dinoszaurusza meghalt.\n");
      return 0;
    } 
    enemy.decHP(temp);
    if (enemy.elet != 0.0D) {
      System.out.println(enemy.nev + " élete " + enemy.nev + " ponttal csökkent. A megmaradt élete: " + Math.round(temp) + ".\n");
      return 0;
    } 
    System.out.println(enemy.nev + " meghótt a gecibe.\n");
    return 1;
  }
  
  public String toString() {
    return this.nev + "(" + this.nev + Math.round(this.elet);
  }
}
