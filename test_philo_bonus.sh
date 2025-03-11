#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Log file setup
LOG_FILE="philo_bonus_test.log"
echo "=== Philosophers Test Results $(date) ===" > $LOG_FILE

# Compile
make -C philo_bonus/
echo "Compilation completed at $(date)" >> $LOG_FILE

# Function to run test with timeout and check output
run_test() {
    local timeout=$1
    local description=$2
    local expected_result=$3
    shift 3
    echo -e "${YELLOW}Testing: $description${NC}"
    echo -e "\nTesting: $description" >> $LOG_FILE
    echo -e "Command: ./philo_bonus $@"
    echo -e "Command: ./philo_bonus $@" >> $LOG_FILE
    echo -e "Expected: $expected_result"
    echo -e "Expected: $expected_result" >> $LOG_FILE
    
    # Run with timeout and capture output
    output=$(timeout $timeout ./philo_bonus/philo_bonus $@ 2>&1)
    status=$?
    echo "Output:" >> $LOG_FILE
    echo "$output" >> $LOG_FILE
    
    # Check result based on expected behavior
    case $expected_result in
        "no_death")
            if [ $status -eq 124 ]; then
                echo -e "${GREEN}✓ Success: No philosopher died within $timeout seconds${NC}"
                echo "✓ Success: No philosopher died within $timeout seconds" >> $LOG_FILE
            else
                echo -e "${RED}✗ Failed: A philosopher died or program terminated unexpectedly${NC}"
                echo "✗ Failed: A philosopher died or program terminated unexpectedly" >> $LOG_FILE
                echo "Last few lines of output:"
                echo "$output" | tail -n 3
                echo "Last few lines of output:" >> $LOG_FILE
                echo "$output" | tail -n 3 >> $LOG_FILE
            fi
            ;;
        "death")
            if [ $status -eq 0 ] || [ $status -eq 1 ]; then
                if echo "$output" | grep -q "died"; then
                    echo -e "${GREEN}✓ Success: Death occurred as expected${NC}"
                    echo "✓ Success: Death occurred as expected" >> $LOG_FILE
                else
                    echo -e "${RED}✗ Failed: No death message found${NC}"
                    echo "✗ Failed: No death message found" >> $LOG_FILE
                fi
            else
                echo -e "${RED}✗ Failed: Unexpected program termination${NC}"
                echo "✗ Failed: Unexpected program termination" >> $LOG_FILE
            fi
            ;;
        "meals_complete")
            if [ $status -eq 0 ]; then
                local meal_count=$(echo "$output" | grep -c "is eating")
                local expected_meals=$5
                local philo_count=$1
                local total_expected=$((philo_count * expected_meals))
                if [ "$meal_count" -eq "$total_expected" ]; then
                    echo -e "${GREEN}✓ Success: All philosophers completed their meals${NC}"
                    echo "✓ Success: All philosophers completed their meals" >> $LOG_FILE
                else
                    echo -e "${RED}✗ Failed: Expected $total_expected meals, got $meal_count${NC}"
                    echo "✗ Failed: Expected $total_expected meals, got $meal_count" >> $LOG_FILE
                fi
            else
                echo -e "${RED}✗ Failed: Program terminated unexpectedly${NC}"
                echo "✗ Failed: Program terminated unexpectedly" >> $LOG_FILE
            fi
            ;;
    esac
    echo "----------------------------------------"
    echo "----------------------------------------" >> $LOG_FILE
    sleep 1
}

# Function to test error cases
test_error() {
    local description=$1
    shift 1
    echo -e "${YELLOW}Testing error case: $description${NC}"
    echo -e "\nTesting error case: $description" >> $LOG_FILE
    echo -e "Command: ./philo_bonus $@"
    echo -e "Command: ./philo_bonus $@" >> $LOG_FILE
    
    # 実行結果とステータスを保存
    output=$(./philo_bonus/philo_bonus $@ 2>&1)
    status=$?
    
    echo "Output:" >> $LOG_FILE
    echo "$output" >> $LOG_FILE
    
    if [ $status -eq 0 ]; then
        echo -e "${RED}✗ Error should have been detected${NC}"
        echo "✗ Error should have been detected" >> $LOG_FILE
    else
        echo -e "${GREEN}✓ Error detected correctly${NC}"
        echo "✓ Error detected correctly" >> $LOG_FILE
    fi
}

echo "=== Starting Philosopher Tests ==="
echo "=== Starting Philosopher Tests ===" >> $LOG_FILE

# 1. Error Cases
echo -e "\n${YELLOW}=== Error Cases ===${NC}"
test_error "No arguments"
test_error "Too few arguments" 4
test_error "Negative number" 4 -410 200 200
test_error "Zero philosophers" 0 800 200 200
test_error "Non-numeric input" a 800 200 200
test_error "Zero meals" 4 410 200 200 0
test_error "Negative meals" 4 410 200 200 -1

# 2. Death Cases
echo -e "\n${YELLOW}=== Death Cases ===${NC}"
run_test 3 "Single philosopher dies" "death" 1 800 200 200
run_test 3 "Death due to long eating time" "death" 4 310 300 300
run_test 3 "Normal death case" "death" 5 590 200 200
run_test 3 "Quick death case" "death" 4 200 205 205

# 3. Meal limit cases
echo -e "\n${YELLOW}=== Meal Limit Cases ===${NC}"
run_test 5 "All reach 7 meals" "meals_complete" 5 800 200 200 7
run_test 5 "All reach 10 meals" "meals_complete" 4 410 200 200 10
run_test 5 "2 philosophers 5 meals each" "meals_complete" 2 400 200 200 5

# 4. Deadlock potential cases
echo -e "\n${YELLOW}=== Deadloc Potential Cases ===${NC}"
run_test 5 "Two philosophers sync" "no_death" 2 400 100 100
run_test 5 "Odd number sync" "no_death" 5 800 200 200

# 5. Timing critical cases
echo -e "\n${YELLOW}=== Timing Critical Cases ===${NC}"
run_test 5 "Border timing case" "no_death" 4 410 200 200
run_test 5 "Short intervals" "no_death" 5 600 150 150
run_test 5 "Extremely short times" "no_death" 3 310 100 100

# 6. Large number cases
echo -e "\n${YELLOW}=== Large Number Cases ==j=${NC}"
run_test 5 "Many philosophers" "no_death" 200 800 200 200
run_test 5 "Maximum time value" "no_death" 4 2147483647 200 200

# 7. Special timing cases
echo -e "\n${YELLOW}=== Special Timing Cases ===${NC}"
run_test 5 "Equal eat/sleep time" "no_death" 4 310 100 100
run_test 5 "Sleep double eat time" "no_death" 3 610 200 400
run_test 5 "Zero sleep time" "no_death" 5 810 200 0

# 8. Normal operation cases
echo -e "\n${YELLOW}=== Normal Operation Cases ===${NC}"
run_test 5 "Standard case" "no_death" 4 410 200 200
run_test 5 "Odd number of philosophers" "no_death" 5 800 200 200
run_test 5 "Minimum multiple philosophers" "no_death" 2 400 200 200

echo -e "\n${GREEN}=== All tests completed ===${NC}"
echo -e "\n=== All tests completed at $(date) ===" >> $LOG_FILE

# Cleanup
make -C philo_bonus/ fclean > /dev/null 2>&1 