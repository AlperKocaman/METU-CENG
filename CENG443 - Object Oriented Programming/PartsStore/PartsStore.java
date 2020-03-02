import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.DecimalFormat;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * This is the PartStore class that utilize the Java 8 Streams & Lambda Expressions
 * @author Alper KOCAMAN
 * @since 30/12/2019
 */
public class PartsStore {


	// stream is a field of PartsStore class
	private Stream<String> pcPartsStream;
	// when stream is consumed, it will be generated from this list
	private List<String> pcPartsStock;

	/**
	 * Constructor method of the PartStore class.
	 * It doesn't take arguments as it's input will be taken from "pcparts.csv" file which should present in the same folder
	 */
	public PartsStore() {

		try {
			// A string stream is generated by using Java NIO class's Files method
			pcPartsStream = Files.lines(Paths.get("pcparts.csv"));
		} catch (IOException e) {
			e.printStackTrace();
		}

		assert pcPartsStream != null;
		// build the pcPartsStock list
		pcPartsStock = pcPartsStream.collect(Collectors.toList());
	}

	/**
	 * Finding the pc parts with given type and brand.
	 * @param type
	 * if type parameter is null, returns all the pc parts belongs to given brand.
	 * @param brand
	 */
	public void FindPartsWithBrand(String type, String brand){
		// regenerate the stream since last operation consumed it
		pcPartsStream = pcPartsStock.stream();

		// find the results by applying lambda expressions on String object.
		pcPartsStream.map(line -> line.split(","))
				.filter(line -> (type == null || line[0].equals(type) ) &&
						(brand.equals(line[1])))
				.map(Arrays::toString)
				.map(line -> line.replace(", ", ","))
				.map(line -> line.substring(1, line.length()-1))
				.forEach(System.out::println);
	}

	/**
	 * This method calculates the total price of the pcparts for given parameters.
	 * If one of the parameters given as null, this method does not check this parameter equality.
	 * @param type
	 * @param brand
	 * @param model
	 */
	public void TotalPrice(String type, String brand, String model){
		// regenerate the stream since last operation consumed it
		pcPartsStream = pcPartsStock.stream();

		// find the results by applying lambda expressions on String object.
		double sum = pcPartsStream.map(line -> line.split(","))
				.filter(line -> (type == null || type.equals(line[0])) &&
				(brand == null || brand.equals(line[1])) &&
				(model == null || model.equals(line[2])) )
				.map(line -> Double.parseDouble(line[line.length-1].split(" ")[0]))
				.reduce(0.0, Double::sum);
		DecimalFormat df = new DecimalFormat("#.##");
		System.out.printf("%.2f USD\n", sum);
	}

	/**
	 * This method deletes the non existing items from the stock.
	 * This can be carried out by removing the corresponding entry from stock list.
	 */
	public void UpdateStock(){
		// take the initial count by using count() method
		pcPartsStream = pcPartsStock.stream();

		/* This value can also be achieved by initialCount = pcPartsStock.size()
		 * However, I used the stream method here for the sake of the homework purpose
		 */
		long initialCount = pcPartsStream.count();

		// regenerate the stream since count operation consumed it
		pcPartsStream = pcPartsStock.stream();

		// find the results by applying lambda expressions on String object.
		pcPartsStock = pcPartsStream
				.filter(line -> !line.substring(line.lastIndexOf(',')).equals(",0.00 USD") )
				.collect(Collectors.toList());

		// This value can also be achieved by updatedCount = pcPartsStock.size() and Intellij gives warning about using size()
		long updatedCount = pcPartsStock.stream().count();

		System.out.println(initialCount - updatedCount + " items removed.");
	}

	/**
	 * This method finds the cheapest memory with equal or grater capacity than given capacity parameter.
	 * @param capacity
	 */
	public void FindCheapestMemory(int capacity){

		// regenerate the stream since count operation consumed it
		pcPartsStream = pcPartsStock.stream();

		// find the results by applying lambda expressions on String object.
		String[] cheapestMemory = pcPartsStream.map(line -> line.split(","))
				.filter(line -> (line[0].equals("Memory") && Integer.parseInt(line[4].substring(0, line[4].length()-2)) >= capacity))
				.min(Comparator.comparingDouble(line -> Double.parseDouble(line[6].substring(0, line[6].length() - 4))))
				.orElseThrow(NoSuchElementException::new);

		System.out.println(Arrays.toString(cheapestMemory).substring(1, Arrays.toString(cheapestMemory).length()-1).replace(", ", ","));
	}

	/**
	 * This method finds the fastest CPU among the CPUs in the stock.
	 * Speed of the CPU is determined by multiplying it's core count with it's clock speed.
	 */
	public void FindFastestCPU(){

		// regenerate the stream since count operation consumed it
		pcPartsStream = pcPartsStock.stream();

		// find the results by applying lambda expressions on String object.
		String[] fastestCPU = pcPartsStream.map(line -> line.split(","))
				.filter(line -> (line[0].equals("CPU") ))
				.max(Comparator.comparingDouble(line -> Double.parseDouble(line[3])*
						Double.parseDouble(line[4].substring(0, line[4].length() -3))))
				.orElseThrow(NoSuchElementException::new);

		System.out.println(Arrays.toString(fastestCPU).substring(1, Arrays.toString(fastestCPU).length()-1).replace(", ", ","));
	}
}
