package core;

import entities.Amazon;
import java.util.HashMap;

public class Player {
    private int spawns;
    private int actives;
    private final HashMap<String, Amazon> amazonMap;


    public Player() {
        this.spawns = 0;
        this.actives = 0;
        this.amazonMap = new HashMap<>();
    }

    
    public int getSpawns() {
        return this.spawns;
    }
    public int getActives() {
        return this.actives;
    }
    public HashMap<String, Amazon> getAmazonMap() {
        return this.amazonMap;
    }


    public void incActive() {
        this.actives++;
    }
    public void decActive() {
        this.actives--;
    }
    public void incSpawn() {
        this.spawns++;
    }


    public boolean hasAmazon(Amazon a) {
        for (HashMap.Entry<String, Amazon> entry : this.amazonMap.entrySet())
            if (entry.getValue().equals(a))
                return true;
        return false;
    }
    public boolean hasAmazon(String name) {
        return this.amazonMap.containsKey(name);
    }
    public void addAmazon (String name) {
        if (!this.amazonMap.containsKey(name))
            this.amazonMap.put(name, new Amazon(name));
    }
    public Amazon getAmazon(String name) {
        if (this.amazonMap.containsKey(name))
            return this.amazonMap.get(name);
        return null;
    }
}