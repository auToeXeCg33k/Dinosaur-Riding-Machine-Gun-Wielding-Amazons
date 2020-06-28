import java.util.HashSet;

public class Tile {
  private HashSet<Amazon> amazonSet = new HashSet<>();
  
  private HashSet<Dinoszaurusz> dinoszauruszSet = new HashSet<>();
  
  public void addAmazon(Amazon a) {
    this.amazonSet.add(a);
  }
  
  public boolean addDinoszaurusz(Dinoszaurusz d) {
    if (this.dinoszauruszSet.contains(d))
      return false; 
    this.dinoszauruszSet.add(d);
    return true;
  }
  
  public void rmAmazon(Amazon a) {
    this.amazonSet.remove(a);
  }
  
  public void rmDinoszaurusz(Dinoszaurusz d) {
    this.dinoszauruszSet.remove(d);
  }
  
  public boolean containsDinoszaurusz(Dinoszaurusz d) {
    return this.dinoszauruszSet.contains(d);
  }
  
  public boolean containsAmazon(Amazon a) {
    return this.amazonSet.contains(a);
  }
  
  public HashSet<Amazon> getAmazonSet() {
    return this.amazonSet;
  }
  
  public HashSet<Dinoszaurusz> getDinoszauruszSet() {
    return this.dinoszauruszSet;
  }
  
  public boolean exists() {
    return true;
  }
}
