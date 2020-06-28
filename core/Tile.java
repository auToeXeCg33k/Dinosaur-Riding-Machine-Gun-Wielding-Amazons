package core;

import entities.Amazon;
import entities.Dinoszaurusz;
import items.Item;
import java.util.ArrayList;
import java.util.HashSet;

public class Tile {
  private HashSet<Amazon> amazonSet = new HashSet<>();
  
  private ArrayList<Dinoszaurusz> dinoszauruszList = new ArrayList<>();
  
  private ArrayList<Item> itemList = new ArrayList<>();
  
  public void addAmazon(Amazon a) {
    this.amazonSet.add(a);
  }
  
  public boolean addDinoszaurusz(Dinoszaurusz d) {
    if (this.dinoszauruszList.contains(d))
      return false; 
    this.dinoszauruszList.add(d);
    return true;
  }
  
  public boolean addItem(Item i) {
    if (this.itemList.contains(i))
      return false; 
    this.itemList.add(i);
    return true;
  }
  
  public boolean spawnDinoszaurusz(Dinoszaurusz d) {
    if (this.dinoszauruszList.isEmpty()) {
      this.dinoszauruszList.add(d);
      return true;
    } 
    return false;
  }
  
  public boolean spawnItem(Item i) {
    if (this.dinoszauruszList.isEmpty()) {
      this.itemList.add(i);
      return true;
    } 
    return false;
  }
  
  public void rmAmazon(Amazon a) {
    this.amazonSet.remove(a);
  }
  
  public void rmDinoszaurusz(Dinoszaurusz d) {
    this.dinoszauruszList.remove(d);
  }
  
  public void rmItem(Item i) {
    this.itemList.remove(i);
  }
  
  public boolean containsAmazon(Amazon a) {
    return this.amazonSet.contains(a);
  }
  
  public boolean containsDinoszaurusz(Dinoszaurusz d) {
    return this.dinoszauruszList.contains(d);
  }
  
  public HashSet<Amazon> getAmazonSet() {
    return this.amazonSet;
  }
  
  public ArrayList<Dinoszaurusz> getDinoszauruszList() {
    return this.dinoszauruszList;
  }
  
  public ArrayList<Item> getItemList() {
    return this.itemList;
  }
}
