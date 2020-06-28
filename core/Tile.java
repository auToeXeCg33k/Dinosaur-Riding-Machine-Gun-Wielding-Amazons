package core;

import entities.Amazon;
import entities.BrainDrainer;
import entities.Dinoszaurusz;
import items.Item;
import java.util.ArrayList;
import java.util.HashSet;

public class Tile {
  private HashSet<Amazon> amazonSet = new HashSet<>();
  
  private ArrayList<Dinoszaurusz> dinoszauruszList = new ArrayList<>();
  
  private ArrayList<Item> itemList = new ArrayList<>();
  
  private BrainDrainer brainDrainer = null;
  
  public void add(Amazon a) {
    this.amazonSet.add(a);
  }
  
  public boolean add(Dinoszaurusz d) {
    if (this.dinoszauruszList.contains(d))
      return false; 
    this.dinoszauruszList.add(d);
    return true;
  }
  
  public boolean add(Item i) {
    if (this.itemList.contains(i))
      return false; 
    this.itemList.add(i);
    return true;
  }
  
  public boolean add(BrainDrainer b) {
    if (this.brainDrainer == null) {
      this.brainDrainer = b;
      return true;
    } 
    return false;
  }
  
  public boolean spawn(Dinoszaurusz d) {
    if (this.dinoszauruszList.isEmpty()) {
      this.dinoszauruszList.add(d);
      return true;
    } 
    return false;
  }
  
  public boolean spawn(Item i) {
    if (this.itemList.isEmpty()) {
      this.itemList.add(i);
      return true;
    } 
    return false;
  }
  
  public boolean spawn() {
    if (this.brainDrainer != null)
      return false; 
    this.brainDrainer = new BrainDrainer();
    return true;
  }
  
  public void remove(Amazon a) {
    this.amazonSet.remove(a);
  }
  
  public void remove(Dinoszaurusz d) {
    this.dinoszauruszList.remove(d);
  }
  
  public void remove(Item i) {
    this.itemList.remove(i);
  }
  
  public BrainDrainer remove() {
    BrainDrainer temp = this.brainDrainer;
    this.brainDrainer = null;
    return temp;
  }
  
  public boolean contains(Amazon a) {
    return this.amazonSet.contains(a);
  }
  
  public boolean contains(Dinoszaurusz d) {
    return this.dinoszauruszList.contains(d);
  }
  
  public boolean contains() {
    return (this.brainDrainer != null);
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
  
  public BrainDrainer getBrainDrainer() {
    return this.brainDrainer;
  }
}
