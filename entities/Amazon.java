package entities;

import items.GepFegyver;
import items.Item;
import java.util.HashMap;


public class Amazon implements Entity {
    private final String nev;
    private double elet;
    private Dinoszaurusz dinoszaurusz;
    private boolean lovagol;
    private final HashMap<Class<?>, Item[]> inventory;
    private GepFegyver gepFegyver;


    public Amazon(String nev) {
        this.nev = nev;
        elet = 100.0;
        dinoszaurusz = null;
        lovagol = false;
        inventory = new HashMap<>();
        this.gepFegyver = null;
        inventory.put(GepFegyver.class, new GepFegyver[2]);
    }


    public String getNev() {
        return this.nev;
    }
    public double getHP() {
        return elet;
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
        for (HashMap.Entry<Class<?>, Item[]> entry : inventory.entrySet()) {
            if (entry.getKey().isInstance(i)) {
                for (int j = 0; j < entry.getValue().length; j++) {
                    if (entry.getValue()[j] == null) {
                        entry.getValue()[j] = i;
                        return true;
                    }
                }
                return false;
            }
        }
        return false;
    }
    public Item dropFromInventory(Class<?> c) {
        for (HashMap.Entry<Class<?>, Item[]> entry : inventory.entrySet()) {
            if (entry.getKey().isAssignableFrom(c)) {
                for (int j = 0; j < entry.getValue().length; j++) {
                    if (c.equals(entry.getValue()[j].getClass())) {
                        Item temp = entry.getValue()[j];
                        entry.getValue()[j] = null;
                        return temp;
                    }
                }
                return null;
            }
        }
        return null;
    }
    public boolean equip(Class<?> c) {
        for (int i = 0; i < inventory.get(GepFegyver.class).length; i++) {
            if (c.isInstance(inventory.get(GepFegyver.class)[i])) {
                this.gepFegyver = (GepFegyver)inventory.get(GepFegyver.class)[i];
                return true;
            }
        }
        return false;
    }


    public void incHP(double r) {
        if (elet + r <= 100.0) {
            elet += r;
            return;
        }
        elet = 100.0;
    }
    public void decHP(double r) {
        if (elet - r >= 0.0) {
            elet -= r;
            return;
        }
        elet = 0.0;
    }


    public void tame(Dinoszaurusz d) {
        this.dinoszaurusz = d;
        d.setTamed(true);
    }


    public String tamad(Amazon enemy) {
        double temp = this.gepFegyver.getDMG();

        if (enemy.isLovagol()) {
            enemy.getDinoszaurusz().decHP(temp);
            if (enemy.getDinoszaurusz().getHP() > 0.0)
                return enemy.nev + " dinoszauruszának élete " + Math.round(temp) + " ponttal csökkent. A megmaradt élete: " + Math.round(enemy.getDinoszaurusz().getHP()) + ".\n";

            enemy.setLovagol(false);
            return enemy.nev + " dinoszaurusza meghalt.\n";
        }

        enemy.decHP(temp);
        if (enemy.elet != 0.0)
            return enemy.nev + " élete " + Math.round(temp) + " ponttal csökkent. A megmaradt élete: " + Math.round(enemy.getHP()) + ".\n";

        return enemy.nev + " meghótt a gecibe.\n";
    }


    @Override
    public String toString() {
        return this.nev + "(" + Math.round(this.elet) + (this.lovagol ? "HP, lovagol, a dinója élete: " + Math.round(this.dinoszaurusz.getHP()) : "HP, nem lovagol") + (this.gepFegyver != null ? ", a kezében egy " + this.gepFegyver + ")" : ", nem fog semmit)");
    }
}