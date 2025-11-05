import static org.junit.Assert.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/**
 * Write a description of class SalesItemTest here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class SalesItemTest
{
    public SalesItemTest(){}

    @Before
    public void setUp() {}
    
    @After
    public void tearDown() {}
    
    @Test
    public void testAddComment()
    {
        SalesItem salesIte1 = new SalesItem("Item1", 12999);
        assertEquals(true, salesIte1.addComment("Felix", "Absolutely loved it", 5));
        assertEquals(1, salesIte1.getNumberOfComments());
    }

    @Test
    public void testIllegalRating()
    {
        SalesItem salesIte1 = new SalesItem("Item1", 12999);
        assertEquals(false, salesIte1.addComment("BadUser", "Terrible product", 0));
    }

    @Test
    public void testDuplicateAuthor()
    {
        SalesItem salesIte1 = new SalesItem("Item1", 12999);
        assertEquals(true, salesIte1.addComment("Felix", "Absolutely loved it", 5));
        assertEquals(false, salesIte1.addComment("Felix", "Could be better", 3));
    }

    @Test
    public void testInit()
    {
        SalesItem salesIte1 = new SalesItem("Sample Item", 1500);
        assertEquals("Sample Item", salesIte1.getName());
        assertEquals(1500, salesIte1.getPrice());
    }

    @Test
    public void addComment()
    {
        SalesItem salesIte1 = new SalesItem("Advanced Gardening Guide", 4999);
        assertEquals(true, salesIte1.addComment("Sam", "Easy to follow, my plants thrive!", 4));
    }
}